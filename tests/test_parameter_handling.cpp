#include <iostream>
#include <string>
#include "zenoh_rpc/jsonrpc_proto.hpp"

using json = nlohmann::json;
using namespace zenoh_rpc;

int main() {
    std::cout << "=== 测试参数处理功能 ===\n\n";
    
    // 测试 1: make_request_args 模板版本自动生成ID
    std::cout << "1. 测试 make_request_args 模板版本自动生成ID:\n";
    json request1 = make_request_args("test_method", "param1", 42, true);
    std::cout << "请求: " << request1.dump(2) << "\n\n";
    
    // 测试 1.1: make_request_args 模板版本指定ID
    std::cout << "1.1. 测试 make_request_args 模板版本指定ID:\n";
    json request1_1 = make_request_args("test_method", "req-001", "param1", 42, true);
    std::cout << "请求: " << request1_1.dump(2) << "\n\n";
    
    // 测试 2: make_request_list 使用初始化列表
    std::cout << "2. 测试 make_request_list 使用初始化列表:\n";
    json request2 = make_request_list("calculate", {10, 20, "add"}, "req-123");
    std::cout << "请求: " << request2.dump(2) << "\n\n";
    
    // 测试 3: make_request_list 自动生成ID
    std::cout << "3. 测试 make_request_list 自动生成ID:\n";
    json request3 = make_request_list("process", {"data1", "data2"});
    std::cout << "请求: " << request3.dump(2) << "\n\n";
    
    // 测试 4: 验证有效请求
    std::cout << "4. 测试请求验证功能:\n";
    json valid_request = {
        {"jsonrpc", "2.0"},
        {"method", "test"},
        {"params", json::array({1, 2, 3})},
        {"id", "test-id"}
    };
    bool is_valid = validate_request(valid_request);
    std::cout << "有效请求验证结果: " << (is_valid ? "通过" : "失败") << "\n";
    std::cout << "请求: " << valid_request.dump(2) << "\n\n";
    
    // 测试 5: 验证无效请求（缺少method）
    std::cout << "5. 测试无效请求验证（缺少method）:\n";
    json invalid_request = {
        {"jsonrpc", "2.0"},
        {"params", json::array({1, 2, 3})},
        {"id", "test-id"}
    };
    bool is_invalid = validate_request(invalid_request);
    std::cout << "无效请求验证结果: " << (is_invalid ? "通过" : "失败") << "\n";
    std::cout << "请求: " << invalid_request.dump(2) << "\n\n";
    
    // 测试 6: 验证有效响应
    std::cout << "6. 测试响应验证功能:\n";
    json valid_response = {
        {"jsonrpc", "2.0"},
        {"result", "success"},
        {"id", "test-id"}
    };
    bool response_valid = validate_response(valid_response);
    std::cout << "有效响应验证结果: " << (response_valid ? "通过" : "失败") << "\n";
    std::cout << "响应: " << valid_response.dump(2) << "\n\n";
    
    // 测试 7: 验证错误响应
    std::cout << "7. 测试错误响应验证:\n";
    json error_response = {
        {"jsonrpc", "2.0"},
        {"error", {
            {"code", -32601},
            {"message", "Method not found"}
        }},
        {"id", "test-id"}
    };
    bool error_valid = validate_response(error_response);
    std::cout << "错误响应验证结果: " << (error_valid ? "通过" : "失败") << "\n";
    std::cout << "响应: " << error_response.dump(2) << "\n\n";
    
    // 测试 8: 验证无效响应（同时包含result和error）
    std::cout << "8. 测试无效响应验证（同时包含result和error）:\n";
    json invalid_response = {
        {"jsonrpc", "2.0"},
        {"result", "success"},
        {"error", {
            {"code", -32601},
            {"message", "Method not found"}
        }},
        {"id", "test-id"}
    };
    bool invalid_resp = validate_response(invalid_response);
    std::cout << "无效响应验证结果: " << (invalid_resp ? "通过" : "失败") << "\n";
    std::cout << "响应: " << invalid_response.dump(2) << "\n\n";
    
    // 测试 9: 复杂参数处理
    std::cout << "9. 测试复杂参数处理:\n";
    json complex_params = {
        {"user", "alice"},
        {"data", {
            {"items", json::array({1, 2, 3})},
            {"metadata", {
                {"timestamp", "2024-01-01T00:00:00Z"},
                {"version", "1.0"}
            }}
        }}
    };
    json complex_request = make_request_kwargs("process_data", complex_params, "complex-123");
    std::cout << "复杂请求: " << complex_request.dump(2) << "\n";
    bool complex_valid = validate_request(complex_request);
    std::cout << "复杂请求验证结果: " << (complex_valid ? "通过" : "失败") << "\n\n";
    
    std::cout << "=== 参数处理功能测试完成 ===\n";
    return 0;
}