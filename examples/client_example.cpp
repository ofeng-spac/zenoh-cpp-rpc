#include <zenoh.hxx>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <string>
#include <nlohmann/json.hpp>

using namespace zenoh;
using namespace std::chrono_literals;
using json = nlohmann::json;

// 发送查询并等待响应的辅助函数
void send_query(Session& session, const std::string& keyexpr, const std::string& payload = "") {
    std::mutex m;
    std::condition_variable done_signal;
    bool done = false;
    int reply_count = 0;
    
    auto on_reply = [&reply_count](const Reply &reply) {
        reply_count++;
        if (reply.is_ok()) {
            const auto &sample = reply.get_ok();
            std::cout << "[客户端] 收到响应 #" << reply_count << " ('" 
                      << sample.get_keyexpr().as_string_view() << "' : '" 
                      << sample.get_payload().as_string() << "')" << std::endl;
        } else {
            std::cout << "[客户端] 收到错误: " << reply.get_err().get_payload().as_string() << std::endl;
        }
    };
    
    auto on_done = [&m, &done, &done_signal]() {
        std::lock_guard lock(m);
        done = true;
        done_signal.notify_all();
    };
    
    Session::GetOptions options;
    options.target = QueryTarget::Z_QUERY_TARGET_BEST_MATCHING;
    options.timeout_ms = 5000; // 5秒超时
    if (!payload.empty()) {
        options.payload = payload;
    }
    
    std::cout << "发送查询到 '" << keyexpr << "'..." << std::endl;
    session.get(keyexpr, "", on_reply, on_done, std::move(options));
    
    // 等待查询完成
    std::unique_lock lock(m);
    if (done_signal.wait_for(lock, 6s, [&done] { return done; })) {
        std::cout << "查询完成，共收到 " << reply_count << " 个响应" << std::endl;
    } else {
        std::cout << "查询超时" << std::endl;
    }
}

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

    std::cout << "RPC Query客户端已启动" << std::endl;
    
    // 等待服务器发现
    std::cout << "等待服务器发现..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\n=== 测试 Echo 方法 ===" << std::endl;
    
    // 测试 echo 方法
    json echo_params;
    echo_params["message"] = "Hello, World!";
    send_query(session, "example/rpc/echo", echo_params.dump());
    
    std::cout << "\n=== 测试 Sum 方法 ===" << std::endl;
    
    // 测试 sum 方法
    json sum_params;
    sum_params["a"] = 10;
    sum_params["b"] = 20;
    send_query(session, "example/rpc/sum", sum_params.dump());
    
    std::cout << "\n=== 测试默认方法 ===" << std::endl;
    
    // 测试默认方法
    send_query(session, "example/rpc/default");
    
    std::cout << "\n=== 测试不存在的方法 ===" << std::endl;
    
    // 测试不存在的方法
    send_query(session, "example/rpc/nonexistent");
    
    std::cout << "\n=== 所有测试完成 ===" << std::endl;
    
    return 0;
}