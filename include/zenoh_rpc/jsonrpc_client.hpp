#pragma once

#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include "session.hpp"
#include "jsonrpc_proto.hpp"

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @file jsonrpc_client.hpp
 * @brief JSON-RPC 客户端实现
 * 
 * 本文件定义了 JSON-RPC 客户端类，提供了调用远程方法的功能。
 * 客户端支持：
 * - 同步方法调用
 * - 超时控制
 * - 自动错误处理
 * - 会话管理（自动创建或使用现有会话）
 */

/**
 * @class Client
 * @brief JSON-RPC 客户端类
 * 
 * 提供调用远程 JSON-RPC 服务的功能。客户端可以使用自己的会话
 * 或者共享现有的会话。支持同步调用和超时控制。
 */
class Client {
public:
    /**
     * @brief 构造函数（自动创建会话）
     * @param key_expr Zenoh 键表达式，用于标识远程服务
     * 
     * 创建一个新的客户端实例，并自动创建一个新的 Zenoh 会话。
     * 客户端将拥有并管理这个会话的生命周期。
     */
    explicit Client(const std::string& key_expr);
    
    /**
     * @brief 构造函数（使用现有会话）
     * @param key_expr Zenoh 键表达式，用于标识远程服务
     * @param session 现有的 Zenoh 会话引用
     * 
     * 创建一个新的客户端实例，使用提供的现有会话。
     * 客户端不会管理会话的生命周期。
     */
    explicit Client(const std::string& key_expr, Session& session);
    
    /**
     * @brief 析构函数
     * 
     * 如果客户端拥有会话，会自动清理会话资源。
     */
    ~Client() = default;

    /**
     * @brief 调用远程方法
     * @param method 要调用的方法名
     * @param params 方法参数（默认为空对象）
     * @param timeout 超时时间（默认为10秒）
     * @return 方法执行结果的 JSON 对象
     * @throws TimeoutError 当请求超时时
     * @throws ConnectionError 当连接失败时
     * @throws RpcError 当远程方法执行出错时
     * 
     * 发送 JSON-RPC 请求到远程服务并等待响应。
     * 如果在指定时间内没有收到响应，会抛出超时异常。
     */
    json call(const std::string& method, const json& params = json::object(), 
              std::chrono::milliseconds timeout = std::chrono::milliseconds(10000));

private:
    std::string key_expr_;                      ///< Zenoh 键表达式
    Session* session_;                          ///< Zenoh 会话指针
    bool owns_session_;                         ///< 是否拥有会话的所有权
    std::unique_ptr<Session> owned_session_;    ///< 拥有的会话实例
};

} // namespace zenoh_rpc