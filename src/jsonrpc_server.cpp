#include "zenoh_rpc/jsonrpc_server.hpp"
#include "zenoh_rpc/errors.hpp"
#include <iostream>
#include <thread>

namespace zenoh_rpc {

void DispatcherBase::register_method(const std::string& method_name, std::function<json(const json&)> handler) {
    methods_[method_name] = std::move(handler);
}

json DispatcherBase::dispatch(const std::string& method_name, const json& params) {
    auto it = methods_.find(method_name);
    if (it == methods_.end()) {
        throw MethodNotFoundError("Method '" + method_name + "' not found");
    }
    return it->second(params);
}

void run_server(const std::string& key_expr, DispatcherBase& dispatcher, Session& session) {
    std::cout << "Starting RPC server on '" << key_expr << "'..." << std::endl;
    
    auto on_query = [&dispatcher](const zenoh::Query& query) {
        try {
            // Get query payload
            auto payload_opt = query.get_payload();
            if (!payload_opt.has_value()) {
                std::cerr << "Received query without payload" << std::endl;
                return;
            }
            
            std::string payload_str = payload_opt->get().as_string();
            std::cout << "Received query with payload: " << payload_str << std::endl;
            
            // Decode JSON-RPC request
            json request = decode_json(payload_str);
            
            // Validate JSON-RPC request
            if (!request.contains("jsonrpc") || request["jsonrpc"] != "2.0" ||
                !request.contains("method") || !request.contains("id")) {
                json error_response = make_response_err(-32600, "Invalid Request", 
                    request.contains("id") ? request["id"].get<std::string>() : "null");
                query.reply(query.get_keyexpr(), encode_json(error_response));
                return;
            }
            
            std::string method = request["method"];
            json params = request.contains("params") ? request["params"] : json::object();
            std::string id = request["id"];
            
            try {
                // Dispatch method call
                json result = dispatcher.dispatch(method, params);
                json response = make_response_ok(result, id);
                query.reply(query.get_keyexpr(), encode_json(response));
            } catch (const MethodNotFoundError& e) {
                json error_response = make_response_err(-32601, e.what(), id);
                query.reply(query.get_keyexpr(), encode_json(error_response));
            } catch (const InvalidParamsError& e) {
                json error_response = make_response_err(-32602, e.what(), id);
                query.reply(query.get_keyexpr(), encode_json(error_response));
            } catch (const std::exception& e) {
                json error_response = make_response_err(-32603, "Internal error: " + std::string(e.what()), id);
                query.reply(query.get_keyexpr(), encode_json(error_response));
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error processing query: " << e.what() << std::endl;
        }
    };
    
    auto queryable = session.declare_queryable(key_expr, on_query);
    
    std::cout << "RPC server running. Press Ctrl+C to stop..." << std::endl;
    
    // Keep the server running
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void run_server(const std::string& key_expr, DispatcherBase& dispatcher) {
    Session session;
    run_server(key_expr, dispatcher, session);
}

} // namespace zenoh_rpc