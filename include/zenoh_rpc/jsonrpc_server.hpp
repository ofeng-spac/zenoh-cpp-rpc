#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>
#include "session.hpp"
#include "jsonrpc_proto.hpp"

namespace zenoh_rpc {

using json = nlohmann::json;

class DispatcherBase {
public:
    virtual ~DispatcherBase() = default;
    
    // Register a method handler
    void register_method(const std::string& method_name, std::function<json(const json&)> handler);
    
    // Dispatch method call
    json dispatch(const std::string& method_name, const json& params);
    
protected:
    std::unordered_map<std::string, std::function<json(const json&)>> methods_;
};

// Run RPC server
void run_server(const std::string& key_expr, DispatcherBase& dispatcher, Session& session);
void run_server(const std::string& key_expr, DispatcherBase& dispatcher);

} // namespace zenoh_rpc