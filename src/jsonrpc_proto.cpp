#include "zenoh_rpc/jsonrpc_proto.hpp"
#include "zenoh_rpc/errors.hpp"
#include <random>
#include <sstream>
#include <iomanip>

namespace zenoh_rpc {

std::string gen_uuid() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    
    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (int i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (int i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 12; i++) {
        ss << dis(gen);
    }
    return ss.str();
}

json make_request(const std::string& method, const json& params, const std::string& id) {
    json request;
    request["jsonrpc"] = "2.0";
    request["method"] = method;
    
    // Only add params if not empty
    if (!params.empty()) {
        request["params"] = params;
    }
    
    // Generate ID if not provided
    std::string request_id = id.empty() ? gen_uuid() : id;
    request["id"] = request_id;
    return request;
}

json make_request_kwargs(const std::string& method, const json& kwargs, const std::string& id) {
    return make_request(method, kwargs, id);
}

json make_response_ok(const json& result, const std::string& id) {
    json response;
    response["jsonrpc"] = "2.0";
    response["result"] = result;
    response["id"] = id;
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

std::string get_encoding() {
    return "application/json";
}

std::pair<std::function<std::string(const json&)>, std::function<json(const std::string&)>> get_encoding_funcs(EncodingType type) {
    switch (type) {
        case EncodingType::JSON:
            return std::make_pair(
                [](const json& data) { return data.dump(); },
                [](const std::string& data) { return json::parse(data); }
            );
        case EncodingType::MSGPACK:
            // For now, fallback to JSON since msgpack is not implemented
            // TODO: Implement msgpack support
            return std::make_pair(
                [](const json& data) { return data.dump(); },
                [](const std::string& data) { return json::parse(data); }
            );
        default:
            throw std::invalid_argument("Unsupported encoding type");
    }
}

std::string encode_json(const json& data) {
    return data.dump();
}

json decode_json(const std::string& data) {
    try {
        return json::parse(data);
    } catch (const json::parse_error& e) {
        throw ParseError("Failed to parse JSON: " + std::string(e.what()));
    }
}

} // namespace zenoh_rpc