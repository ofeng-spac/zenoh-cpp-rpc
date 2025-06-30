#include "zenoh_rpc/jsonrpc_server.hpp"
#include "zenoh_rpc/errors.hpp"
#include <iostream>

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @brief 注册方法处理器
 * @param method_name 方法名称
 * @param handler 方法处理函数
 * 
 * 将方法名与其处理函数关联起来。
 * 如果方法名已存在，会覆盖原有的处理函数。
 */
void DispatcherBase::register_method(const std::string& method_name, std::function<json(const json&)> handler) {
    methods_[method_name] = handler;
}

/**
 * @brief 分发方法调用
 * @param method_name 要调用的方法名
 * @param params 方法参数
 * @return 方法执行结果
 * @throws MethodNotFoundError 当方法不存在时
 * 
 * 根据方法名查找对应的处理函数并执行。
 * 如果方法不存在，会抛出 MethodNotFoundError 异常。
 */
json DispatcherBase::dispatch(const std::string& method_name, const json& params) {
    auto it = methods_.find(method_name);
    if (it == methods_.end()) {
        throw MethodNotFoundError("Method '" + method_name + "' not found");
    }
    return it->second(params);
}

/**
 * @brief 运行 RPC 服务器（使用现有会话）
 * @param key_expr Zenoh 键表达式，用于标识服务
 * @param dispatcher 方法分发器引用
 * @param session 现有的 Zenoh 会话引用
 * 
 * 启动 JSON-RPC 服务器，处理传入的请求并返回响应。
 * 服务器会持续运行，直到程序终止。
 * 
 * 处理流程：
 * 1. 接收 Zenoh 查询请求
 * 2. 解析 JSON-RPC 请求
 * 3. 验证请求格式
 * 4. 调用对应的方法处理器
 * 5. 生成并发送 JSON-RPC 响应
 */
void run_server(const std::string& key_expr, DispatcherBase& dispatcher, Session& session) {
    std::cout << "Starting RPC server on '" << key_expr << "'..." << std::endl;
    
    // 定义查询处理回调函数
    auto on_query = [&dispatcher](const zenoh::Query& query) {
        try {
            // 获取查询载荷
            auto payload_opt = query.get_payload();
            if (!payload_opt.has_value()) {
                std::cerr << "Received query without payload" << std::endl;
                return;
            }
            
            std::string payload_str = payload_opt->get().as_string();
            std::cout << "Received query with payload: " << payload_str << std::endl;
            
            // 解码 JSON-RPC 请求
            json request = decode_json(payload_str);
            
            // 验证 JSON-RPC 请求格式
            if (!request.contains("jsonrpc") || request["jsonrpc"] != "2.0" ||
                !request.contains("method") || !request.contains("id")) {
                json error_response = make_response_err(-32600, "Invalid Request", 
                    request.contains("id") ? request["id"].get<std::string>() : "null");
                query.reply(query.get_keyexpr(), encode_json(error_response));
                return;
            }
            
            // 提取请求字段
            std::string method = request["method"];
            json params = request.contains("params") ? request["params"] : json::object();
            std::string id = request["id"];
            
            try {
                // 分发方法调用
                json result = dispatcher.dispatch(method, params);
                json response = make_response_ok(result, id);
                query.reply(query.get_keyexpr(), encode_json(response));
            } catch (const RpcError& e) {
                // 处理 RPC 错误，包含正确的错误代码和数据
                json error_response = make_response_err(e.get_code(), e.what(), id, e.get_data());
                query.reply(query.get_keyexpr(), encode_json(error_response));
            } catch (const std::exception& e) {
                // 处理其他异常
                json error_response = make_response_err(-32603, "Internal error: " + std::string(e.what()), id);
                query.reply(query.get_keyexpr(), encode_json(error_response));
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error processing query: " << e.what() << std::endl;
        }
    };
    
    // 声明可查询对象
    auto queryable = session.declare_queryable(key_expr, on_query);
    
    std::cout << "RPC server running. Press Ctrl+C to stop..." << std::endl;
    
    // 保持服务器运行
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/**
 * @brief 运行 RPC 服务器（自动创建会话）
 * @param key_expr Zenoh 键表达式，用于标识服务
 * @param dispatcher 方法分发器引用
 * 
 * 便利函数，自动创建新的 Zenoh 会话并启动服务器。
 * 适用于不需要共享会话的场景。
 */
void run_server(const std::string& key_expr, DispatcherBase& dispatcher) {
    Session session;
    run_server(key_expr, dispatcher, session);
}

} // namespace zenoh_rpc