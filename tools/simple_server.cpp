#include <iostream>
#include <zenoh_rpc/zenoh_rpc.hpp>
#include <thread>
#include <chrono>

using namespace zenoh_rpc;
using json = nlohmann::json;

class SimpleDispatcher : public DispatcherBase {
public:
    SimpleDispatcher() {
        // 注册ping方法
        register_method("ping", [this](const json& params) -> json {
            return this->ping(params);
        });
        
        // 注册echo方法
        register_method("echo", [this](const json& params) -> json {
            return this->echo(params);
        });
    }
    
private:
    json ping(const json& params) {
        std::cout << "Received ping request" << std::endl;
        return json{{"response", "pong"}};
    }
    
    json echo(const json& params) {
        std::cout << "Received echo request: " << params.dump() << std::endl;
        return params;
    }
};

int main() {
    try {
        std::cout << "Starting simple test server..." << std::endl;
        
        // 创建简单的RPC服务器
        auto dispatcher = std::make_shared<SimpleDispatcher>();
        
        std::cout << "Server registered methods: ping, echo" << std::endl;
        
        // 以CLIENT模式运行服务器，连接到默认zenohd路由器
        run_server("test/simple", *dispatcher, SessionMode::CLIENT, {"tcp/127.0.0.1:7447"});
        
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}