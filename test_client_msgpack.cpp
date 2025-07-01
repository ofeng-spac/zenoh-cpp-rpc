#include <iostream>
#include <iomanip>
#include "include/zenoh_rpc/jsonrpc_proto.hpp"
#include "include/zenoh_rpc/errors.hpp"

using namespace zenoh_rpc;
using json = nlohmann::json;

int main() {
    std::cout << "Testing Client MessagePack encoding support..." << std::endl;
    
    try {
        // 测试 JSON-RPC 请求的创建和编码
        std::cout << "\n1. Testing JSON-RPC request creation..." << std::endl;
        json request = make_request("test_method", {
            {"arg1", "hello"},
            {"arg2", 42},
            {"arg3", true}
        }, "test-123");
        
        std::cout << "Original request:" << std::endl;
        std::cout << std::setw(2) << request << std::endl;
        
        // 测试 JSON 编码
        std::cout << "\n2. Testing JSON encoding..." << std::endl;
        std::string json_encoded = encode_json(request);
        std::cout << "JSON encoded size: " << json_encoded.size() << " bytes" << std::endl;
        
        // 测试 MessagePack 编码
        std::cout << "\n3. Testing MessagePack encoding..." << std::endl;
        std::string msgpack_encoded = encode_msgpack(request);
        std::cout << "MessagePack encoded size: " << msgpack_encoded.size() << " bytes" << std::endl;
        
        // 显示压缩效果
        std::cout << "Compression ratio: " << std::fixed << std::setprecision(2) 
                  << (double)msgpack_encoded.size() / json_encoded.size() * 100 << "%" << std::endl;
        
        // 测试解码
        std::cout << "\n4. Testing decoding..." << std::endl;
        json json_decoded = decode_json(json_encoded);
        json msgpack_decoded = decode_msgpack(msgpack_encoded);
        
        if (request == json_decoded && request == msgpack_decoded) {
            std::cout << "✓ SUCCESS: Both encodings decode correctly!" << std::endl;
        } else {
            std::cout << "✗ FAILURE: Decoding mismatch!" << std::endl;
            return 1;
        }
        
        // 测试编码函数选择机制
        std::cout << "\n5. Testing encoding function selection..." << std::endl;
        auto json_funcs = get_encoding_funcs(EncodingType::JSON);
        auto msgpack_funcs = get_encoding_funcs(EncodingType::MSGPACK);
        
        std::string json_result = json_funcs.first(request);
        json json_func_decoded = json_funcs.second(json_result);
        
        std::string msgpack_result = msgpack_funcs.first(request);
        json msgpack_func_decoded = msgpack_funcs.second(msgpack_result);
        
        if (request == json_func_decoded && request == msgpack_func_decoded) {
            std::cout << "✓ SUCCESS: Encoding function pairs work correctly!" << std::endl;
        } else {
            std::cout << "✗ FAILURE: Encoding function pairs failed!" << std::endl;
            return 1;
        }
        
        // 测试响应编码
        std::cout << "\n6. Testing response encoding..." << std::endl;
        json success_response = make_response_ok({"result", "success"}, "test-123");
        json error_response = make_response_err(-32600, "Invalid Request", "test-123");
        
        std::string success_json = encode_json(success_response);
        std::string success_msgpack = encode_msgpack(success_response);
        std::string error_json = encode_json(error_response);
        std::string error_msgpack = encode_msgpack(error_response);
        
        json success_json_decoded = decode_json(success_json);
        json success_msgpack_decoded = decode_msgpack(success_msgpack);
        json error_json_decoded = decode_json(error_json);
        json error_msgpack_decoded = decode_msgpack(error_msgpack);
        
        if (success_response == success_json_decoded && 
            success_response == success_msgpack_decoded &&
            error_response == error_json_decoded &&
            error_response == error_msgpack_decoded) {
            std::cout << "✓ SUCCESS: Response encoding works correctly!" << std::endl;
        } else {
            std::cout << "✗ FAILURE: Response encoding failed!" << std::endl;
            return 1;
        }
        
        std::cout << "\n🎉 All Client MessagePack tests passed successfully!" << std::endl;
        std::cout << "\nMessagePack encoding is fully integrated and working." << std::endl;
        
    } catch (const ParseError& e) {
        std::cout << "Parse Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}