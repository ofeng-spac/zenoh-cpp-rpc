#pragma once

#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @file errors.hpp
 * @brief Zenoh RPC 错误处理系统
 * 
 * 本文件定义了 Zenoh RPC 框架中使用的所有异常类型。
 * 这些异常类型遵循 JSON-RPC 2.0 规范中定义的错误代码标准。
 * 
 * 错误代码说明：
 * - ParseError: -32700 (解析错误)
 * - InvalidRequestError: -32600 (无效请求)
 * - MethodNotFoundError: -32601 (方法未找到)
 * - InvalidParamsError: -32602 (无效参数)
 * - InternalError: -32603 (内部错误)
 * - ServerError: -32000 (服务器错误)
 * - ConnectionError: -32001 (连接错误)
 * - TimeoutError: -32002 (超时错误)
 */

/**
 * @class RpcError
 * @brief RPC 异常基类
 * 
 * 所有 RPC 相关异常的基类，继承自 std::runtime_error。
 * 提供了错误代码和附加数据的支持，符合 JSON-RPC 2.0 规范。
 */
class RpcError : public std::runtime_error {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息
     * @param code 错误代码（默认为0）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit RpcError(const std::string& message, int code = 0, const json& data = json::object()) 
        : std::runtime_error(message), code_(code), data_(data) {}
    
    /**
     * @brief 获取错误代码
     * @return 错误代码
     */
    int get_code() const { return code_; }
    
    /**
     * @brief 获取附加错误数据
     * @return 附加错误数据的JSON对象
     */
    const json& get_data() const { return data_; }
    
private:
    int code_;      ///< 错误代码
    json data_;     ///< 附加错误数据
};

/**
 * @class ParseError
 * @brief JSON 解析错误异常
 * 
 * 当服务器接收到无效的 JSON 数据时抛出此异常。
 * 错误代码：-32700
 */
class ParseError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit ParseError(const std::string& message = "Invalid JSON was received by the server", const json& data = json::object()) 
        : RpcError(message, -32700, data) {}
};

/**
 * @class InvalidRequestError
 * @brief 无效请求异常
 * 
 * 当发送的 JSON 不是有效的请求对象时抛出此异常。
 * 错误代码：-32600
 */
class InvalidRequestError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit InvalidRequestError(const std::string& message = "The JSON sent is not a valid Request object", const json& data = json::object()) 
        : RpcError(message, -32600, data) {}
};

/**
 * @class MethodNotFoundError
 * @brief 方法未找到异常
 * 
 * 当请求的方法不存在或不可用时抛出此异常。
 * 错误代码：-32601
 */
class MethodNotFoundError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit MethodNotFoundError(const std::string& message = "The method does not exist / is not available", const json& data = json::object()) 
        : RpcError(message, -32601, data) {}
};

/**
 * @class InvalidParamsError
 * @brief 无效参数异常
 * 
 * 当方法参数无效时抛出此异常。
 * 错误代码：-32602
 */
class InvalidParamsError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit InvalidParamsError(const std::string& message = "Invalid method parameter(s)", const json& data = json::object()) 
        : RpcError(message, -32602, data) {}
};

/**
 * @class InternalError
 * @brief 内部错误异常
 * 
 * 当发生内部 JSON-RPC 错误时抛出此异常。
 * 错误代码：-32603
 */
class InternalError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit InternalError(const std::string& message = "Internal JSON-RPC error", const json& data = json::object()) 
        : RpcError(message, -32603, data) {}
};

/**
 * @class ServerError
 * @brief 服务器错误异常
 * 
 * 当服务器发生错误时抛出此异常。
 * 错误代码：-32000
 */
class ServerError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit ServerError(const std::string& message = "Server error", const json& data = json::object()) 
        : RpcError(message, -32000, data) {}
};

/**
 * @class ConnectionError
 * @brief 连接错误异常
 * 
 * 当连接到服务器失败时抛出此异常。
 * 错误代码：-32001
 */
class ConnectionError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit ConnectionError(const std::string& message = "Connection to server failed", const json& data = json::object()) 
        : RpcError(message, -32001, data) {}
};

/**
 * @class TimeoutError
 * @brief 超时错误异常
 * 
 * 当请求超时时抛出此异常。
 * 错误代码：-32002
 */
class TimeoutError : public RpcError {
public:
    /**
     * @brief 构造函数
     * @param message 错误消息（默认为标准消息）
     * @param data 附加错误数据（默认为空对象）
     */
    explicit TimeoutError(const std::string& message = "Request timed out", const json& data = json::object()) 
        : RpcError(message, -32002, data) {}
};

} // namespace zenoh_rpc