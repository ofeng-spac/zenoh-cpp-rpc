#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>
#include "session.hpp"
#include "jsonrpc_proto.hpp"

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @file jsonrpc_server.hpp
 * @brief JSON-RPC 服务器实现
 * 
 * 本文件定义了 JSON-RPC 服务器的核心组件，包括：
 * - 方法分发器基类
 * - 服务器运行函数
 * - 方法注册和调用机制
 * 
 * 服务器特性：
 * - 自动请求解析和响应生成
 * - 错误处理和异常转换
 * - 方法动态注册
 * - 支持自定义会话或自动创建会话
 */

/**
 * @class DispatcherBase
 * @brief 方法分发器基类
 * 
 * 负责管理和分发 JSON-RPC 方法调用。提供方法注册和调用的基础功能。
 * 用户可以继承此类来实现自定义的方法分发逻辑。
 */
class DispatcherBase {
public:
    /**
     * @brief 虚析构函数
     * 
     * 确保派生类能够正确析构。
     */
    virtual ~DispatcherBase() = default;
    
    /**
     * @brief 注册方法处理器
     * @param method_name 方法名称
     * @param handler 方法处理函数
     * 
     * 将一个方法名与其处理函数关联起来。
     * 处理函数接受 JSON 参数并返回 JSON 结果。
     */
    void register_method(const std::string& method_name, std::function<json(const json&)> handler);
    
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
    json dispatch(const std::string& method_name, const json& params);
    
protected:
    /// 方法名到处理函数的映射表
    std::unordered_map<std::string, std::function<json(const json&)>> methods_;
};

/**
 * @brief 运行 RPC 服务器（使用现有会话）
 * @param key_expr Zenoh 键表达式，用于标识服务
 * @param dispatcher 方法分发器引用
 * @param session 现有的 Zenoh 会话引用
 * 
 * 启动 JSON-RPC 服务器，使用提供的会话监听指定键表达式上的请求。
 * 服务器会持续运行，处理传入的 JSON-RPC 请求并返回响应。
 * 
 * 处理流程：
 * 1. 接收 Zenoh 查询请求
 * 2. 解析 JSON-RPC 请求
 * 3. 验证请求格式
 * 4. 调用对应的方法处理器
 * 5. 生成并发送 JSON-RPC 响应
 */
void run_server(const std::string& key_expr, DispatcherBase& dispatcher, Session& session);

/**
 * @brief 运行 RPC 服务器（自动创建会话）
 * @param key_expr Zenoh 键表达式，用于标识服务
 * @param dispatcher 方法分发器引用
 * 
 * 启动 JSON-RPC 服务器，自动创建新的 Zenoh 会话。
 * 这是 run_server 的便利重载版本，适用于不需要共享会话的场景。
 */
void run_server(const std::string& key_expr, DispatcherBase& dispatcher);

/**
 * @brief 运行 RPC 服务器（自动创建会话，指定模式和连接）
 * @param key_expr Zenoh 键表达式，用于标识服务
 * @param dispatcher 方法分发器引用
 * @param mode 会话模式（client/peer/router）
 * @param connections 连接端点列表
 * 
 * 启动 JSON-RPC 服务器，使用指定的模式和连接端点创建新的 Zenoh 会话。
 * 适用于需要特定网络配置的服务器场景。
 */
void run_server(const std::string& key_expr, DispatcherBase& dispatcher, 
                SessionMode mode, const std::vector<std::string>& connections = {});

} // namespace zenoh_rpc