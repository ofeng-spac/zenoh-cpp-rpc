/**
 * @file session_management_example.cpp
 * @brief Session 管理功能示例
 * 
 * 本示例演示了 zenoh-cpp-rpc 库中完善的 Session 管理功能，包括：
 * - 不同会话模式的使用（client/peer/router）
 * - 连接端点配置
 * - 会话生命周期管理
 * - 客户端和服务器的会话配置
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "zenoh_rpc/jsonrpc_client.hpp"
#include "zenoh_rpc/jsonrpc_server.hpp"
#include "zenoh_rpc/errors.hpp"

using namespace zenoh_rpc;
using json = nlohmann::json;

/**
 * @class ExampleDispatcher
 * @brief 示例方法分发器
 * 
 * 实现一些简单的 RPC 方法用于演示。
 */
class ExampleDispatcher : public DispatcherBase {
public:
    ExampleDispatcher() {
        // 注册示例方法
        register_method("add", [](const json& params) -> json {
            if (!params.is_array() || params.size() != 2) {
                throw InvalidParamsError("add method requires exactly 2 parameters");
            }
            return params[0].get<double>() + params[1].get<double>();
        });
        
        register_method("echo", [](const json& params) -> json {
            return params;
        });
        
        register_method("get_info", [](const json& params) -> json {
            return json{{
                {"service", "example_service"},
                {"version", "1.0.0"},
                {"timestamp", std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count()}
            }};
        });
    }
};

/**
 * @brief 演示基本会话管理
 */
void demo_basic_session() {
    std::cout << "\n=== 基本会话管理演示 ===\n";
    
    // 创建默认会话
    Session session;
    std::cout << "创建默认会话，模式: " << 
        (session.get_mode() == SessionMode::PEER ? "PEER" : "OTHER") << std::endl;
    std::cout << "会话状态: " << (session.is_active() ? "活动" : "非活动") << std::endl;
    
    // 手动关闭会话
    session.close();
    std::cout << "关闭会话后状态: " << (session.is_active() ? "活动" : "非活动") << std::endl;
}

/**
 * @brief 演示不同会话模式
 */
void demo_session_modes() {
    std::cout << "\n=== 会话模式演示 ===\n";
    
    // 创建 CLIENT 模式会话
    {
        Session client_session(SessionMode::CLIENT);
        std::cout << "CLIENT 模式会话创建成功" << std::endl;
        std::cout << "模式: " << 
            (client_session.get_mode() == SessionMode::CLIENT ? "CLIENT" : "OTHER") << std::endl;
    }
    
    // 创建 PEER 模式会话
    {
        Session peer_session(SessionMode::PEER);
        std::cout << "PEER 模式会话创建成功" << std::endl;
        std::cout << "模式: " << 
            (peer_session.get_mode() == SessionMode::PEER ? "PEER" : "OTHER") << std::endl;
    }
    
    // 创建 ROUTER 模式会话
    {
        Session router_session(SessionMode::ROUTER);
        std::cout << "ROUTER 模式会话创建成功" << std::endl;
        std::cout << "模式: " << 
            (router_session.get_mode() == SessionMode::ROUTER ? "ROUTER" : "OTHER") << std::endl;
    }
}

/**
 * @brief 演示连接端点配置
 */
void demo_connection_endpoints() {
    std::cout << "\n=== 连接端点配置演示 ===\n";
    
    // 配置连接端点
    std::vector<std::string> endpoints = {
        "tcp/127.0.0.1:7447",
        "tcp/localhost:7448"
    };
    
    Session session(SessionMode::CLIENT, endpoints);
    std::cout << "创建带连接端点的 CLIENT 会话" << std::endl;
    std::cout << "配置的端点数量: " << session.get_connections().size() << std::endl;
    
    for (const auto& endpoint : session.get_connections()) {
        std::cout << "  - " << endpoint << std::endl;
    }
}

/**
 * @brief 演示客户端会话配置
 */
void demo_client_session_config() {
    std::cout << "\n=== 客户端会话配置演示 ===\n";
    
    // 使用默认配置的客户端
    {
        Client client("example/service");
        std::cout << "创建默认配置客户端成功" << std::endl;
    }
    
    // 使用指定模式和端点的客户端
    {
        std::vector<std::string> endpoints = {"tcp/127.0.0.1:7447"};
        Client client("example/service", SessionMode::CLIENT, endpoints);
        std::cout << "创建指定配置客户端成功" << std::endl;
    }
    
    // 使用共享会话的客户端
    {
        Session shared_session(SessionMode::PEER);
        Client client1("example/service1", shared_session);
        Client client2("example/service2", shared_session);
        std::cout << "创建共享会话的多个客户端成功" << std::endl;
    }
}

/**
 * @brief 演示服务器会话配置
 */
void demo_server_session_config() {
    std::cout << "\n=== 服务器会话配置演示 ===\n";
    
    ExampleDispatcher dispatcher;
    
    // 注意：这里只演示服务器创建，不实际运行
    // 实际运行会阻塞当前线程
    
    std::cout << "可以使用以下方式启动服务器：" << std::endl;
    std::cout << "1. 默认配置: run_server(\"example/service\", dispatcher)" << std::endl;
    std::cout << "2. 指定模式: run_server(\"example/service\", dispatcher, SessionMode::PEER)" << std::endl;
    std::cout << "3. 指定端点: run_server(\"example/service\", dispatcher, SessionMode::CLIENT, endpoints)" << std::endl;
    std::cout << "4. 共享会话: run_server(\"example/service\", dispatcher, session)" << std::endl;
}

/**
 * @brief 演示会话生命周期管理
 */
void demo_session_lifecycle() {
    std::cout << "\n=== 会话生命周期管理演示 ===\n";
    
    {
        Session session(SessionMode::PEER);
        std::cout << "会话创建: " << (session.is_active() ? "活动" : "非活动") << std::endl;
        
        // 会话在作用域结束时自动析构和关闭
        std::cout << "会话即将离开作用域..." << std::endl;
    }
    std::cout << "会话已自动析构" << std::endl;
    
    // 手动管理会话生命周期
    Session* session = new Session(SessionMode::CLIENT);
    std::cout << "动态创建会话: " << (session->is_active() ? "活动" : "非活动") << std::endl;
    
    session->close();
    std::cout << "手动关闭会话: " << (session->is_active() ? "活动" : "非活动") << std::endl;
    
    delete session;
    std::cout << "手动删除会话" << std::endl;
}

int main() {
    std::cout << "zenoh-cpp-rpc Session 管理功能演示\n";
    std::cout << "====================================\n";
    
    try {
        demo_basic_session();
        demo_session_modes();
        demo_connection_endpoints();
        demo_client_session_config();
        demo_server_session_config();
        demo_session_lifecycle();
        
        std::cout << "\n=== 演示完成 ===\n";
        std::cout << "所有 Session 管理功能演示成功！\n";
        
    } catch (const std::exception& e) {
        std::cerr << "演示过程中发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}