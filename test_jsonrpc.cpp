#include <iostream>
#include <zenoh_rpc/jsonrpc_proto.hpp>
#include <zenoh_rpc/errors.hpp>

int main() {
    std::cout << "=== Zenoh C++ RPC Library Test ===" << std::endl;
    
    try {
        // Test JSON-RPC request creation
        auto request = zenoh_rpc::make_request("test_method", nlohmann::json{{"param1", "value1"}}, "1");
        std::cout << "Created JSON-RPC request: " << request.dump(2) << std::endl;
        
        // Test JSON-RPC response creation
        auto response = zenoh_rpc::make_response_ok(nlohmann::json{{"result", "success"}}, "1");
        std::cout << "Created JSON-RPC response: " << response.dump(2) << std::endl;
        
        // Test error response creation
        auto error_response = zenoh_rpc::make_response_err(-32601, "Method not found", "1");
        std::cout << "Created JSON-RPC error response: " << error_response.dump(2) << std::endl;
        
        // Test encoding/decoding
        std::string encoded = zenoh_rpc::encode_json(request);
        std::cout << "Encoded JSON: " << encoded << std::endl;
        
        auto decoded = zenoh_rpc::decode_json(encoded);
        std::cout << "Decoded JSON: " << decoded.dump(2) << std::endl;
        
        // Test error classes
        try {
            throw zenoh_rpc::MethodNotFoundError("Test method not found");
        } catch (const zenoh_rpc::RpcError& e) {
            std::cout << "Caught RPC error: " << e.what() << std::endl;
        }
        
        std::cout << "\n=== All tests passed! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}