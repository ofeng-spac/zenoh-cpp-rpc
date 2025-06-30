#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
#include <iomanip>

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @file jsonrpc_proto.hpp
 * @brief JSON-RPC 协议处理模块
 * 
 * 本文件定义了 JSON-RPC 2.0 协议的核心功能，包括：
 * - 请求和响应消息的创建
 * - UUID 生成
 * - 编码和解码功能
 * - 参数处理（位置参数和关键字参数）
 * 
 * 支持的编码格式：
 * - JSON（完全支持）
 * - MessagePack（计划支持）
 */

/**
 * @brief 生成 UUID
 * @return 生成的 UUID 字符串
 * 
 * 生成符合 UUID v4 标准的唯一标识符，用于 JSON-RPC 请求的 ID 字段。
 * 格式：xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
 */
std::string gen_uuid();

/**
 * @brief 创建 JSON-RPC 请求
 * @param method 要调用的方法名
 * @param params 方法参数（可以是对象或数组，默认为空对象）
 * @param id 请求ID（如果为空则自动生成）
 * @return 格式化的 JSON-RPC 请求对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的请求消息。
 * 请求格式：{"jsonrpc": "2.0", "method": "...", "params": {...}, "id": "..."}
 */
json make_request(const std::string& method, const json& params = json::object(), const std::string& id = "");

/**
 * @brief 使用位置参数创建 JSON-RPC 请求
 * @tparam Args 参数类型包
 * @param method 要调用的方法名
 * @param id 请求ID
 * @param args 位置参数列表
 * @return 格式化的 JSON-RPC 请求对象
 * 
 * 使用可变参数模板创建带有位置参数的 JSON-RPC 请求。
 * 参数将被打包成 JSON 数组。
 */
template<typename... Args>
json make_request_args(const std::string& method, const std::string& id, Args&&... args) {
    json params = json::array();
    (params.push_back(std::forward<Args>(args)), ...);
    return make_request(method, params, id);
}

/**
 * @brief 使用关键字参数创建 JSON-RPC 请求
 * @param method 要调用的方法名
 * @param kwargs 关键字参数对象
 * @param id 请求ID（如果为空则自动生成）
 * @return 格式化的 JSON-RPC 请求对象
 * 
 * 创建带有命名参数的 JSON-RPC 请求。
 * 参数将作为 JSON 对象传递。
 */
json make_request_kwargs(const std::string& method, const json& kwargs, const std::string& id = "");

/**
 * @brief 创建成功的 JSON-RPC 响应
 * @param result 方法执行结果
 * @param id 对应请求的ID
 * @return 格式化的成功响应对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的成功响应消息。
 * 响应格式：{"jsonrpc": "2.0", "result": {...}, "id": "..."}
 */
json make_response_ok(const json& result, const std::string& id);

/**
 * @brief 创建错误的 JSON-RPC 响应
 * @param code 错误代码
 * @param message 错误消息
 * @param id 对应请求的ID
 * @return 格式化的错误响应对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的错误响应消息。
 * 响应格式：{"jsonrpc": "2.0", "error": {"code": ..., "message": "..."}, "id": "..."}
 */
json make_response_err(int code, const std::string& message, const std::string& id);

/**
 * @brief 创建带有附加数据的错误 JSON-RPC 响应
 * @param code 错误代码
 * @param message 错误消息
 * @param id 对应请求的ID
 * @param data 附加错误数据
 * @return 格式化的错误响应对象
 * 
 * 创建包含附加错误信息的 JSON-RPC 错误响应。
 * 响应格式：{"jsonrpc": "2.0", "error": {"code": ..., "message": "...", "data": {...}}, "id": "..."}
 */
json make_response_err(int code, const std::string& message, const std::string& id, const json& data);

/**
 * @enum EncodingType
 * @brief 编码类型枚举
 * 
 * 定义支持的消息编码格式。
 */
enum class EncodingType {
    JSON,       ///< JSON 编码格式（完全支持）
    MSGPACK     ///< MessagePack 编码格式（计划支持）
};

/**
 * @brief 获取当前编码类型字符串
 * @return 编码类型字符串
 * 
 * 返回当前使用的编码格式的 MIME 类型字符串。
 * 用于与 Python 版本保持兼容性。
 */
std::string get_encoding();

/**
 * @brief 获取编码和解码函数对
 * @param type 编码类型
 * @return 编码和解码函数的配对
 * 
 * 根据指定的编码类型返回对应的编码和解码函数。
 * 返回值：{编码函数, 解码函数}
 */
std::pair<std::function<std::string(const json&)>, std::function<json(const std::string&)>> get_encoding_funcs(EncodingType type);

/**
 * @brief 将 JSON 对象编码为字符串
 * @param data 要编码的 JSON 对象
 * @return 编码后的字符串
 * 
 * 将 JSON 对象序列化为紧凑的字符串格式。
 */
std::string encode_json(const json& data);

/**
 * @brief 将字符串解码为 JSON 对象
 * @param data 要解码的字符串
 * @return 解码后的 JSON 对象
 * @throws ParseError 当字符串不是有效的 JSON 格式时
 * 
 * 将字符串反序列化为 JSON 对象。
 * 如果解析失败，会抛出 ParseError 异常。
 */
json decode_json(const std::string& data);

} // namespace zenoh_rpc