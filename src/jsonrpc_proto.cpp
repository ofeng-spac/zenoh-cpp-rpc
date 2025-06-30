#include "zenoh_rpc/jsonrpc_proto.hpp"
#include "zenoh_rpc/errors.hpp"
#include <random>
#include <sstream>
#include <iomanip>

namespace zenoh_rpc {

using json = nlohmann::json;

/**
 * @brief 生成 UUID v4 字符串
 * @return 格式为 xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx 的 UUID 字符串
 * 
 * 生成符合 RFC 4122 标准的 UUID v4。
 * 使用随机数生成器确保唯一性，适用于 JSON-RPC 请求 ID。
 * 
 * UUID 格式说明：
 * - 第13位固定为4（版本号）
 * - 第17位为8-b之间的值（变体标识）
 * - 其余位为随机十六进制数字
 */
std::string gen_uuid() {
    static std::random_device rd;  ///< 硬件随机数生成器
    static std::mt19937 gen(rd()); ///< 梅森旋转算法随机数生成器
    static std::uniform_int_distribution<> dis(0, 15);  ///< 0-15的均匀分布（十六进制数字）
    static std::uniform_int_distribution<> dis2(8, 11); ///< 8-11的均匀分布（UUID变体标识）
    
    std::stringstream ss;
    int i;
    ss << std::hex;
    
    // 生成前8位
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    
    // 生成4位
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";  // 版本号4
    
    // 生成3位
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    
    // 生成变体标识和3位
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    
    // 生成最后12位
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    }
    return ss.str();
}

/**
 * @brief 创建 JSON-RPC 请求（带指定ID）
 * @param method 要调用的方法名
 * @param params 方法参数（JSON对象或数组）
 * @param id 请求标识符
 * @return 完整的 JSON-RPC 请求对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的请求对象。
 * 请求包含必需的 jsonrpc、method、params 和 id 字段。
 */
json make_request(const std::string& method, const json& params, const std::string& id) {
    json request;
    request["jsonrpc"] = "2.0";  // JSON-RPC 版本
    request["method"] = method;   // 方法名
    request["params"] = params;   // 参数
    request["id"] = id;           // 请求ID
    return request;
}

/**
 * @brief 创建 JSON-RPC 请求（自动生成ID）
 * @param method 要调用的方法名
 * @param params 方法参数（JSON对象或数组）
 * @return 完整的 JSON-RPC 请求对象
 * 
 * 便利函数，自动生成 UUID 作为请求ID。
 * 适用于不需要手动管理请求ID的场景。
 */
json make_request(const std::string& method, const json& params) {
    return make_request(method, params, gen_uuid());
}

/**
 * @brief 创建无参数的 JSON-RPC 请求
 * @param method 要调用的方法名
 * @return 完整的 JSON-RPC 请求对象
 * 
 * 便利函数，用于调用不需要参数的方法。
 * 参数字段将设置为空的 JSON 对象。
 */
json make_request(const std::string& method) {
    return make_request(method, json::object());
}

/**
 * @brief 创建带关键字参数的 JSON-RPC 请求（带指定ID）
 * @param method 要调用的方法名
 * @param kwargs 关键字参数（JSON对象）
 * @param id 请求标识符
 * @return 完整的 JSON-RPC 请求对象
 * 
 * 用于创建使用关键字参数的 JSON-RPC 请求。
 * 参数必须是 JSON 对象格式，键为参数名，值为参数值。
 */
json make_request_kwargs(const std::string& method, const json& kwargs, const std::string& id) {
    return make_request(method, kwargs, id);
}

/**
 * @brief 创建带关键字参数的 JSON-RPC 请求（自动生成ID）
 * @param method 要调用的方法名
 * @param kwargs 关键字参数（JSON对象）
 * @return 完整的 JSON-RPC 请求对象
 * 
 * 便利函数，自动生成 UUID 作为请求ID。
 */
json make_request_kwargs(const std::string& method, const json& kwargs) {
    return make_request_kwargs(method, kwargs, gen_uuid());
}

/**
 * @brief 创建成功的 JSON-RPC 响应
 * @param result 方法执行结果
 * @param id 对应请求的ID
 * @return JSON-RPC 成功响应对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的成功响应。
 * 响应包含 jsonrpc、result 和 id 字段。
 */
json make_response_ok(const json& result, const std::string& id) {
    json response;
    response["jsonrpc"] = "2.0";  // JSON-RPC 版本
    response["result"] = result;   // 执行结果
    response["id"] = id;           // 对应的请求ID
    return response;
}

json make_response_err(int code, const std::string& message, const std::string& id) {
    json response;
    response["jsonrpc"] = "2.0";
    response["error"] = {
        {"code", code},
        {"message", message}
    };
    response["id"] = id;
    return response;
}

/**
 * @brief 创建错误的 JSON-RPC 响应
 * @param code 错误代码
 * @param message 错误消息
 * @param id 对应请求的ID
 * @param data 附加错误数据（可选）
 * @return JSON-RPC 错误响应对象
 * 
 * 创建符合 JSON-RPC 2.0 规范的错误响应。
 * 响应包含 jsonrpc、error 和 id 字段。
 * error 字段包含 code、message 和可选的 data。
 */
json make_response_err(int code, const std::string& message, const std::string& id, const json& data) {
    json response;
    response["jsonrpc"] = "2.0";  // JSON-RPC 版本
    response["error"] = {
        {"code", code},
        {"message", message}
    };
    
    // Only add data field if it's not empty
    if (!data.empty() && !data.is_null()) {
        response["error"]["data"] = data;  // 附加错误数据
    }
    
    response["id"] = id;           // 对应的请求ID
    return response;
}

/**
 * @brief 获取默认编码类型
 * @return 默认编码类型字符串
 * 
 * 返回当前使用的默认编码类型。
 * 目前固定返回 "application/json"。
 */
std::string get_encoding() {
    return "application/json";
}

/**
 * @brief 获取指定编码类型的编码/解码函数对
 * @param type 编码类型枚举值
 * @return 编码和解码函数的配对
 * @throws std::invalid_argument 当编码类型不支持时
 * 
 * 根据指定的编码类型返回对应的编码和解码函数。
 * 返回的 pair 中：
 * - first: 编码函数 (json -> string)
 * - second: 解码函数 (string -> json)
 * 
 * 支持的编码类型：
 * - JSON: 标准 JSON 编码
 * - MSGPACK: MessagePack 编码（当前回退到 JSON）
 */
std::pair<std::function<std::string(const json&)>, std::function<json(const std::string&)>> get_encoding_funcs(EncodingType type) {
    switch (type) {
        case EncodingType::JSON:
            return std::make_pair(
                [](const json& data) { return data.dump(); },
                [](const std::string& data) { return json::parse(data); }
            );
        case EncodingType::MSGPACK:
            // 目前回退到 JSON，因为 msgpack 尚未实现
            // TODO: 实现 msgpack 支持
            return std::make_pair(
                [](const json& data) { return data.dump(); },
                [](const std::string& data) { return json::parse(data); }
            );
        default:
            throw std::invalid_argument("Unsupported encoding type");
    }
}

/**
 * @brief 将 JSON 对象编码为字符串
 * @param data 要编码的 JSON 对象
 * @return 编码后的 JSON 字符串
 * 
 * 将 JSON 对象序列化为紧凑的字符串格式。
 * 使用 nlohmann::json 的 dump() 方法进行序列化。
 */
std::string encode_json(const json& data) {
    return data.dump();
}

/**
 * @brief 将字符串解码为 JSON 对象
 * @param data 要解码的 JSON 字符串
 * @return 解码后的 JSON 对象
 * @throws ParseError 当 JSON 解析失败时
 * 
 * 将 JSON 字符串反序列化为 JSON 对象。
 * 如果解析失败，会抛出 ParseError 异常，包含详细的错误信息。
 */
json decode_json(const std::string& data) {
    try {
        return json::parse(data);
    } catch (const json::parse_error& e) {
        throw ParseError("Failed to parse JSON: " + std::string(e.what()));
    }
}

} // namespace zenoh_rpc