#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// 简化的 msgpack 编码解码函数（直接使用 nlohmann::json）
std::string encode_msgpack_simple(const json& data) {
    std::vector<std::uint8_t> msgpack_data = json::to_msgpack(data);
    return std::string(msgpack_data.begin(), msgpack_data.end());
}

json decode_msgpack_simple(const std::string& data) {
    std::vector<std::uint8_t> msgpack_data(data.begin(), data.end());
    return json::from_msgpack(msgpack_data);
}

int main() {
    std::cout << "Testing MessagePack encoding and decoding support..." << std::endl;
    
    try {
        // 测试基本的 JSON 数据
        json test_data = {
            {"method", "test_method"},
            {"params", {
                {"arg1", "hello"},
                {"arg2", 42},
                {"arg3", true}
            }},
            {"id", "test-123"}
        };
        
        std::cout << "\n1. Original JSON data:" << std::endl;
        std::cout << std::setw(2) << test_data << std::endl;
        
        // 测试 MessagePack 编码
        std::cout << "\n2. Testing MessagePack encoding..." << std::endl;
        std::string msgpack_encoded = encode_msgpack_simple(test_data);
        std::cout << "MessagePack encoded size: " << msgpack_encoded.size() << " bytes" << std::endl;
        
        // 显示编码后的字节（十六进制）
        std::cout << "MessagePack bytes (hex): ";
        for (unsigned char byte : msgpack_encoded) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        }
        std::cout << std::dec << std::endl;
        
        // 测试 MessagePack 解码
        std::cout << "\n3. Testing MessagePack decoding..." << std::endl;
        json decoded_data = decode_msgpack_simple(msgpack_encoded);
        std::cout << "Decoded JSON data:" << std::endl;
        std::cout << std::setw(2) << decoded_data << std::endl;
        
        // 验证数据一致性
        std::cout << "\n4. Verifying data consistency..." << std::endl;
        if (test_data == decoded_data) {
            std::cout << "✓ SUCCESS: Original and decoded data match!" << std::endl;
        } else {
            std::cout << "✗ FAILURE: Data mismatch!" << std::endl;
            return 1;
        }
        
        // 比较 JSON 和 MessagePack 的大小
        std::string json_encoded = test_data.dump();
        std::cout << "\n5. Size comparison:" << std::endl;
        std::cout << "JSON size: " << json_encoded.size() << " bytes" << std::endl;
        std::cout << "MessagePack size: " << msgpack_encoded.size() << " bytes" << std::endl;
        std::cout << "Compression ratio: " << std::fixed << std::setprecision(2) 
                  << (double)msgpack_encoded.size() / json_encoded.size() * 100 << "%" << std::endl;
        
        // 测试更复杂的数据结构
        std::cout << "\n6. Testing complex data structures..." << std::endl;
        json complex_data = {
            {"array", {1, 2, 3, "test", true, nullptr}},
            {"nested", {
                {"level1", {
                    {"level2", "deep value"}
                }}
            }},
            {"numbers", {
                {"int", 42},
                {"float", 3.14159},
                {"negative", -123}
            }}
        };
        
        std::string complex_msgpack = encode_msgpack_simple(complex_data);
        json complex_decoded = decode_msgpack_simple(complex_msgpack);
        
        if (complex_data == complex_decoded) {
            std::cout << "✓ SUCCESS: Complex data structures work correctly!" << std::endl;
        } else {
            std::cout << "✗ FAILURE: Complex data structure test failed!" << std::endl;
            return 1;
        }
        
        std::cout << "\n🎉 All MessagePack tests passed successfully!" << std::endl;
        std::cout << "\nMessagePack support is working correctly with nlohmann::json library." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}