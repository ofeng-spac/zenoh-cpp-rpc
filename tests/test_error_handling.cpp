#include "zenoh_rpc/errors.hpp"
#include "zenoh_rpc/jsonrpc_proto.hpp"
#include <iostream>
#include <cassert>

using namespace zenoh_rpc;

void test_error_classes() {
    std::cout << "Testing error classes..." << std::endl;
    
    // Test ParseError
    try {
        throw ParseError("Custom parse error", json{{"line", 42}});
    } catch (const ParseError& e) {
        assert(e.get_code() == -32700);
        assert(e.get_data()["line"] == 42);
        std::cout << "ParseError: " << e.what() << ", code: " << e.get_code() << ", data: " << e.get_data().dump() << std::endl;
    }
    
    // Test MethodNotFoundError with default message
    try {
        throw MethodNotFoundError();
    } catch (const MethodNotFoundError& e) {
        assert(e.get_code() == -32601);
        assert(e.get_data().empty());
        std::cout << "MethodNotFoundError: " << e.what() << ", code: " << e.get_code() << std::endl;
    }
    
    // Test InvalidParamsError with custom data
    try {
        json error_data = {
            {"expected", "string"},
            {"received", "number"}
        };
        throw InvalidParamsError("Type mismatch", error_data);
    } catch (const InvalidParamsError& e) {
        assert(e.get_code() == -32602);
        assert(e.get_data()["expected"] == "string");
        std::cout << "InvalidParamsError: " << e.what() << ", code: " << e.get_code() << ", data: " << e.get_data().dump() << std::endl;
    }
    
    std::cout << "All error class tests passed!" << std::endl;
}

void test_error_response_generation() {
    std::cout << "\nTesting error response generation..." << std::endl;
    
    // Test error response without data
    json response1 = make_response_err(-32601, "Method not found", "123");
    assert(response1["jsonrpc"] == "2.0");
    assert(response1["error"]["code"] == -32601);
    assert(response1["error"]["message"] == "Method not found");
    assert(response1["id"] == "123");
    assert(!response1["error"].contains("data"));
    std::cout << "Response without data: " << response1.dump() << std::endl;
    
    // Test error response with data
    json error_data = {{"method", "unknown_method"}, {"available", json::array({"echo", "sum"})}};
    json response2 = make_response_err(-32601, "Method not found", "456", error_data);
    assert(response2["jsonrpc"] == "2.0");
    assert(response2["error"]["code"] == -32601);
    assert(response2["error"]["message"] == "Method not found");
    assert(response2["id"] == "456");
    assert(response2["error"].contains("data"));
    assert(response2["error"]["data"]["method"] == "unknown_method");
    std::cout << "Response with data: " << response2.dump() << std::endl;
    
    // Test error response with empty data (should not include data field)
    json response3 = make_response_err(-32602, "Invalid params", "789", json::object());
    assert(!response3["error"].contains("data"));
    std::cout << "Response with empty data: " << response3.dump() << std::endl;
    
    std::cout << "All error response generation tests passed!" << std::endl;
}

void test_error_code_consistency() {
    std::cout << "\nTesting error code consistency with Python version..." << std::endl;
    
    // Verify all error codes match Python version
    ParseError parse_err;
    assert(parse_err.get_code() == -32700);
    
    InvalidRequestError invalid_req_err;
    assert(invalid_req_err.get_code() == -32600);
    
    MethodNotFoundError method_not_found_err;
    assert(method_not_found_err.get_code() == -32601);
    
    InvalidParamsError invalid_params_err;
    assert(invalid_params_err.get_code() == -32602);
    
    InternalError internal_err;
    assert(internal_err.get_code() == -32603);
    
    ServerError server_err;
    assert(server_err.get_code() == -32000);
    
    ConnectionError conn_err;
    assert(conn_err.get_code() == -32001);
    
    TimeoutError timeout_err;
    assert(timeout_err.get_code() == -32002);
    
    std::cout << "All error codes match Python version!" << std::endl;
}

int main() {
    try {
        test_error_classes();
        test_error_response_generation();
        test_error_code_consistency();
        
        std::cout << "\n✅ All error handling tests passed successfully!" << std::endl;
        std::cout << "\n🎯 Error handling system improvements completed:" << std::endl;
        std::cout << "   - Added code and data fields to all exception classes" << std::endl;
        std::cout << "   - Error codes match Python version exactly" << std::endl;
        std::cout << "   - Support for error data in JSON-RPC responses" << std::endl;
        std::cout << "   - Improved client and server error handling" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}