#pragma once

#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include "session.hpp"
#include "jsonrpc_proto.hpp"

namespace zenoh_rpc {

using json = nlohmann::json;

class Client {
public:
    explicit Client(const std::string& key_expr);
    explicit Client(const std::string& key_expr, Session& session);
    ~Client() = default;

    // Call remote method
    json call(const std::string& method, const json& params = json::object(), 
              std::chrono::milliseconds timeout = std::chrono::milliseconds(10000));

private:
    std::string key_expr_;
    Session* session_;
    bool owns_session_;
    std::unique_ptr<Session> owned_session_;
};

} // namespace zenoh_rpc