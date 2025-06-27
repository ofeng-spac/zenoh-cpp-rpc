#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
#include <iomanip>

namespace zenoh_rpc {

using json = nlohmann::json;

// Generate UUID
std::string gen_uuid();

// Create JSON-RPC request with flexible parameters
json make_request(const std::string& method, const json& params = json::object(), const std::string& id = "");

// Create JSON-RPC request with positional arguments
template<typename... Args>
json make_request_args(const std::string& method, const std::string& id, Args&&... args) {
    json params = json::array();
    (params.push_back(std::forward<Args>(args)), ...);
    return make_request(method, params, id);
}

// Create JSON-RPC request with keyword arguments
json make_request_kwargs(const std::string& method, const json& kwargs, const std::string& id = "");

// Create successful JSON-RPC response
json make_response_ok(const json& result, const std::string& id);

// Create error JSON-RPC response
json make_response_err(int code, const std::string& message, const std::string& id);

// Encoding types
enum class EncodingType {
    JSON,
    MSGPACK
};

// Get encoding type string (for compatibility with Python version)
std::string get_encoding();

// Get encoding functions
std::pair<std::function<std::string(const json&)>, std::function<json(const std::string&)>> get_encoding_funcs(EncodingType type);

// Encode JSON to string
std::string encode_json(const json& data);

// Decode string to JSON
json decode_json(const std::string& data);

} // namespace zenoh_rpc