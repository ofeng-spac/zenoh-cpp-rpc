#include "zenoh_rpc/jsonrpc_client.hpp"
#include "zenoh_rpc/errors.hpp"
#include <iostream>
#include <sstream>
#include <random>

namespace zenoh_rpc {

static std::string generate_id() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
}

Client::Client(const std::string& key_expr) 
    : key_expr_(key_expr), session_(nullptr), owns_session_(true) {
    owned_session_ = std::make_unique<Session>();
    session_ = owned_session_.get();
}

Client::Client(const std::string& key_expr, Session& session) 
    : key_expr_(key_expr), session_(&session), owns_session_(false) {
}

json Client::call(const std::string& method, const json& params, std::chrono::milliseconds timeout) {
    // Generate unique request ID
    std::string id = generate_id();
    
    // Create JSON-RPC request
    json request = make_request(method, params, id);
    std::string request_str = encode_json(request);
    
    std::cout << "Sending request: " << request_str << std::endl;
    
    // Create querier
    auto querier = session_->declare_querier(key_expr_);
    
    // Send query
    zenoh::Querier::GetOptions options;
    options.payload = request_str;
    options.timeout_ms = static_cast<uint64_t>(timeout.count());
    
    auto replies = querier.get("", zenoh::channels::FifoChannel(16), std::move(options));
    
    // Wait for reply
    auto reply_result = replies.recv();
    
    if (!std::holds_alternative<zenoh::Reply>(reply_result)) {
        throw TimeoutError("No reply received within timeout");
    }
    
    const auto& reply = std::get<zenoh::Reply>(reply_result);
    
    if (!reply.is_ok()) {
        throw ConnectionError("Received error reply");
    }
    
    const auto& sample = reply.get_ok();
    std::string response_str = sample.get_payload().as_string();
    
    std::cout << "Received response: " << response_str << std::endl;
    
    // Parse JSON-RPC response
    json response = decode_json(response_str);
    
    // Validate response
    if (!response.contains("jsonrpc") || response["jsonrpc"] != "2.0" ||
        !response.contains("id") || response["id"] != id) {
        throw InvalidRequestError("Invalid JSON-RPC response");
    }
    
    // Check for error
    if (response.contains("error")) {
        json error = response["error"];
        int code = error["code"];
        std::string message = error["message"];
        
        switch (code) {
            case -32700:
                throw ParseError(message);
            case -32600:
                throw InvalidRequestError(message);
            case -32601:
                throw MethodNotFoundError(message);
            case -32602:
                throw InvalidParamsError(message);
            case -32603:
                throw InternalError(message);
            default:
                throw ServerError(message);
        }
    }
    
    // Return result
    if (!response.contains("result")) {
        throw InvalidRequestError("Response missing result field");
    }
    
    return response["result"];
}

} // namespace zenoh_rpc