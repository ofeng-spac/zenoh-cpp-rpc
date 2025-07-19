#include <iostream>
#include <zenoh_rpc/zenoh_rpc.hpp>
#include <chrono>
#include <thread>

using namespace zenoh_rpc;
using json = nlohmann::json;

int main() {
    try {
        std::cout << "Starting simple test client..." << std::endl;
        
        // 创建客户端，使用CLIENT模式连接到默认zenohd路由器
        Client client("test/simple", SessionMode::CLIENT, {"tcp/127.0.0.1:7447"});
        
        std::cout << "Client created, waiting for server discovery..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // 测试ping方法
        std::cout << "\n=== Testing ping method ===" << std::endl;
        json ping_result = client.call("ping", json{});
        std::cout << "Ping result: " << ping_result.dump() << std::endl;
        
        // 测试echo方法
        std::cout << "\n=== Testing echo method ===" << std::endl;
        json echo_params;
        echo_params["message"] = "Hello from simple client!";
        echo_params["timestamp"] = std::time(nullptr);
        
        json echo_result = client.call("echo", echo_params);
        std::cout << "Echo result: " << echo_result.dump() << std::endl;
        
        std::cout << "\n=== Communication test successful! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        std::cout << "This indicates a network connectivity issue." << std::endl;
        return 1;
    }
    
    return 0;
}