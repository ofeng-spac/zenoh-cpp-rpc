#include <zenoh.hxx>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace zenoh;
using namespace std::chrono_literals;
using json = nlohmann::json;

int main(int argc, char **argv) {
    Config config = Config::create_default();
    if (argc > 1) {
        config = Config::from_file(argv[1]);
    } else {
        // 配置为client模式，连接到zenohd路由器
        config.insert_json5("mode", "\"client\"");
        config.insert_json5("connect/endpoints", "[\"tcp/127.0.0.1:7449\"]");
        std::cout << "使用默认配置：连接到 zenohd 路由器 127.0.0.1:7449" << std::endl;
    }

    std::cout << "正在打开会话..." << std::endl;
    auto session = Session::open(std::move(config));

    std::cout << "正在声明Queryable..." << std::endl;
    
    // Echo服务处理函数
    auto on_query_echo = [](const Query &query) {
        auto query_payload = query.get_payload();
        
        std::cout << ">> [Echo服务] 收到查询 '" << query.get_keyexpr().as_string_view() << "'";
        if (query_payload.has_value()) {
            std::cout << " 携带数据 = '" << query_payload->get().as_string() << "'";
        }
        std::cout << std::endl;
        
        std::string response;
        if (query_payload.has_value()) {
            try {
                // 解析JSON参数
                json params = json::parse(query_payload->get().as_string());
                std::cout << "[Echo服务] 解析参数: " << params.dump() << std::endl;
                
                if (params.contains("message")) {
                    response = params["message"];
                } else {
                    response = "Error: Missing 'message' parameter";
                }
            } catch (const std::exception& e) {
                response = "Error: Invalid JSON parameters";
            }
        } else {
            response = "Error: No payload provided";
        }
        
        std::cout << "[Echo服务] 响应: '" << response << "'" << std::endl;
        query.reply(query.get_keyexpr(), response);
    };
    
    // Sum服务处理函数
    auto on_query_sum = [](const Query &query) {
        auto query_payload = query.get_payload();
        
        std::cout << ">> [Sum服务] 收到查询 '" << query.get_keyexpr().as_string_view() << "'";
        if (query_payload.has_value()) {
            std::cout << " 携带数据 = '" << query_payload->get().as_string() << "'";
        }
        std::cout << std::endl;
        
        std::string response;
        if (query_payload.has_value()) {
            try {
                // 解析JSON参数
                json params = json::parse(query_payload->get().as_string());
                std::cout << "[Sum服务] 解析参数: " << params.dump() << std::endl;
                
                if (params.contains("a") && params.contains("b")) {
                    if (params["a"].is_number() && params["b"].is_number()) {
                        double a = params["a"];
                        double b = params["b"];
                        double result = a + b;
                        response = std::to_string(result);
                    } else {
                        response = "Error: Parameters 'a' and 'b' must be numbers";
                    }
                } else {
                    response = "Error: Missing 'a' or 'b' parameter";
                }
            } catch (const std::exception& e) {
                response = "Error: Invalid JSON parameters";
            }
        } else {
            response = "Error: No payload provided";
        }
        
        std::cout << "[Sum服务] 响应: '" << response << "'" << std::endl;
        query.reply(query.get_keyexpr(), response);
    };
    
    // 默认服务处理函数
    auto on_query_default = [](const Query &query) {
        auto query_payload = query.get_payload();
        
        std::cout << ">> [默认服务] 收到查询 '" << query.get_keyexpr().as_string_view() << "'";
        if (query_payload.has_value()) {
            std::cout << " 携带数据 = '" << query_payload->get().as_string() << "'";
        }
        std::cout << std::endl;
        
        std::string response = "Hello from RPC Queryable server! Available methods: echo, sum";
        std::cout << "[默认服务] 响应: '" << response << "'" << std::endl;
        query.reply(query.get_keyexpr(), response);
    };
    
    auto on_drop_queryable = []() {
        std::cout << "销毁 queryable" << std::endl;
    };
    
    // 创建独立的QueryableOptions副本
    Session::QueryableOptions opts1;
    opts1.complete = true;
    Session::QueryableOptions opts2;
    opts2.complete = true;
    Session::QueryableOptions opts3;
    opts3.complete = true;
    
    // 声明三个独立的 Queryable
    auto queryable_echo = session.declare_queryable("example/rpc/echo", on_query_echo, on_drop_queryable, std::move(opts1));
    auto queryable_sum = session.declare_queryable("example/rpc/sum", on_query_sum, on_drop_queryable, std::move(opts2));
    auto queryable_default = session.declare_queryable("example/rpc/default", on_query_default, on_drop_queryable, std::move(opts3));
    
    std::cout << "RPC Queryable服务器已启动，监听键表达式:" << std::endl;
    std::cout << "  - example/rpc/echo (Echo服务)" << std::endl;
    std::cout << "  - example/rpc/sum (Sum服务)" << std::endl;
    std::cout << "  - example/rpc/default (默认服务)" << std::endl;
    std::cout << "按 CTRL-C 退出..." << std::endl;
    
    while (true) {
        std::this_thread::sleep_for(1s);
    }
    
    return 0;
}