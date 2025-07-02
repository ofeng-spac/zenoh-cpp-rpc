#include "zenoh_rpc/jsonrpc_client.hpp"
#include "zenoh_rpc/errors.hpp"
#include <chrono>

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @brief 构造函数（自动创建会话）
 * @param key_expr Zenoh 键表达式，用于标识远程服务
 * @param encoding 编码格式，支持 "json" 和 "msgpack"
 * @param timeout 默认超时时间（毫秒）
 * 
 * 创建新的 Zenoh 会话并初始化查询器。
 * 适用于独立使用客户端的场景。
 */
Client::Client(const std::string& key_expr, const std::string& encoding, std::chrono::milliseconds timeout) 
    : key_expr_(key_expr), 
      session_(nullptr), 
      owns_session_(true),
      owned_session_(std::make_unique<Session>()),
      encoding_(encoding),
      default_timeout_(timeout),
      querier_(owned_session_->declare_querier(key_expr, default_timeout_.count())) {
    session_ = owned_session_.get();
    
    // 验证编码格式
    if (encoding_ != "json" && encoding_ != "msgpack") {
        throw std::invalid_argument("Unsupported encoding: " + encoding_ + ". Supported: json, msgpack");
    }
}

/**
 * @brief 构造函数（自动创建会话，指定模式和连接）
 * @param key_expr Zenoh 键表达式，用于标识远程服务
 * @param mode 会话模式（client/peer/router）
 * @param connections 连接端点列表
 * @param encoding 编码格式，支持 "json" 和 "msgpack"
 * @param timeout 默认超时时间（毫秒）
 * 
 * 使用指定的模式和连接端点创建新的 Zenoh 会话并初始化查询器。
 * 适用于需要特定网络配置的场景。
 */
Client::Client(const std::string& key_expr, SessionMode mode, const std::vector<std::string>& connections, 
               const std::string& encoding, std::chrono::milliseconds timeout) 
    : key_expr_(key_expr), 
      session_(nullptr), 
      owns_session_(true),
      owned_session_(std::make_unique<Session>(mode, connections)),
      encoding_(encoding),
      default_timeout_(timeout),
      querier_(owned_session_->declare_querier(key_expr, default_timeout_.count())) {
    session_ = owned_session_.get();
    
    // 验证编码格式
    if (encoding_ != "json" && encoding_ != "msgpack") {
        throw std::invalid_argument("Unsupported encoding: " + encoding_ + ". Supported: json, msgpack");
    }
}

/**
 * @brief 构造函数（使用现有会话）
 * @param key_expr Zenoh 键表达式，用于标识远程服务
 * @param session 现有的 Zenoh 会话引用
 * @param encoding 编码格式，支持 "json" 和 "msgpack"
 * @param timeout 默认超时时间（毫秒）
 * 
 * 使用提供的会话初始化查询器。
 * 适用于需要共享会话的场景。
 */
Client::Client(const std::string& key_expr, Session& session, const std::string& encoding, std::chrono::milliseconds timeout) 
    : key_expr_(key_expr),
      session_(&session), 
      owns_session_(false),
      encoding_(encoding),
      default_timeout_(timeout),
      querier_(session.declare_querier(key_expr, default_timeout_.count())) {
    
    // 验证编码格式
    if (encoding_ != "json" && encoding_ != "msgpack") {
        throw std::invalid_argument("Unsupported encoding: " + encoding_ + ". Supported: json, msgpack");
    }
}



/**
 * @brief 调用远程 RPC 方法
 * @param method 要调用的方法名
 * @param params 方法参数（JSON对象或数组）
 * @param timeout 超时时间（毫秒）
 * @return 方法执行结果
 * @throws ParseError JSON解析错误
 * @throws InvalidRequestError 无效请求
 * @throws MethodNotFoundError 方法不存在
 * @throws InvalidParamsError 参数无效
 * @throws InternalError 服务器内部错误
 * @throws ServerError 服务器错误
 * @throws ConnectionError 连接错误
 * @throws TimeoutError 超时错误
 * 
 * 执行完整的 RPC 调用流程：
 * 1. 生成唯一请求ID
 * 2. 创建JSON-RPC请求
 * 3. 通过Zenoh发送查询
 * 4. 等待并接收响应
 * 5. 解析和验证响应
 * 6. 处理错误或返回结果
 */
json Client::call(const std::string& method, const json& params, std::optional<std::chrono::milliseconds> timeout) {
    // 使用提供的超时时间或默认超时时间
    auto actual_timeout = timeout.value_or(default_timeout_);
    // 生成唯一的请求ID
    std::string id = gen_uuid();
    
    // 创建 JSON-RPC 请求
    json request = make_request(method, params, id);
    std::string request_str;
    
    // 根据编码格式选择编码函数
    if (encoding_ == "json") {
        request_str = encode_json(request);
    } else if (encoding_ == "msgpack") {
        request_str = encode_msgpack(request);
    } else {
        throw std::invalid_argument("Unsupported encoding: " + encoding_);
    }
    
    // 发送 Zenoh 查询
    zenoh::Querier::GetOptions options;
    options.payload = request_str;
    
    auto replies = querier_.get("", zenoh::channels::FifoChannel(16), std::move(options));
    
    // 等待回复
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
    
    // 根据编码格式解析响应
    json response;
    if (encoding_ == "json") {
        response = decode_json(response_str);
    } else if (encoding_ == "msgpack") {
        response = decode_msgpack(response_str);
    } else {
        throw std::invalid_argument("Unsupported encoding: " + encoding_);
    }
    
    // 验证响应格式
    if (!response.contains("jsonrpc") || response["jsonrpc"] != "2.0" ||
        !response.contains("id") || response["id"] != id) {
        throw InvalidRequestError("Invalid JSON-RPC response");
    }
    
    // 检查是否有错误
    if (response.contains("error")) {
        json error = response["error"];
        int code = error["code"];
        std::string message = error["message"];
        json data = error.contains("data") ? error["data"] : json::object();
        
        // 根据错误代码抛出相应的异常
        switch (code) {
            case -32700:  // 解析错误
                throw ParseError(message, data);
            case -32600:  // 无效请求
                throw InvalidRequestError(message, data);
            case -32601:  // 方法不存在
                throw MethodNotFoundError(message, data);
            case -32602:  // 参数无效
                throw InvalidParamsError(message, data);
            case -32603:  // 内部错误
                throw InternalError(message, data);
            case -32000:  // 服务器错误
                throw ServerError(message, data);
            case -32001:  // 连接错误
                throw ConnectionError(message, data);
            case -32002:  // 超时错误
                throw TimeoutError(message, data);
            default:      // 其他错误
                throw ServerError(message, data);
        }
    }
    
    // 返回执行结果
    if (!response.contains("result")) {
        throw InvalidRequestError("Response missing result field");
    }
    
    return response["result"];
}

} // namespace zenoh_rpc