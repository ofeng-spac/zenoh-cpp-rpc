#include <iostream>
#include <zenoh_rpc/zenoh_rpc.hpp>

using namespace zenoh_rpc;
using json = nlohmann::json;

int main() {
    try {
        // Create client
        Client client("example/rpc");
        
        std::cout << "=== Testing echo method ===" << std::endl;
        
        // Test echo method
        json echo_params;
        echo_params["message"] = "Hello, World!";
        
        json echo_result = client.call("echo", echo_params);
        std::cout << "Echo result: " << echo_result.dump() << std::endl;
        
        std::cout << "\n=== Testing sum method ===" << std::endl;
        
        // Test sum method
        json sum_params;
        sum_params["a"] = 10;
        sum_params["b"] = 20;
        
        json sum_result = client.call("sum", sum_params);
        std::cout << "Sum result: " << sum_result.dump() << std::endl;
        
        std::cout << "\n=== Testing error case ===" << std::endl;
        
        // Test error case - method not found
        try {
            json error_result = client.call("nonexistent_method", json::object());
        } catch (const MethodNotFoundError& e) {
            std::cout << "Expected error caught: " << e.what() << std::endl;
        }
        
        std::cout << "\n=== All tests completed ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}