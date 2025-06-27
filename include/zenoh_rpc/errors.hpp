#pragma once

#include <stdexcept>
#include <string>

namespace zenoh_rpc {

class RpcError : public std::runtime_error {
public:
    explicit RpcError(const std::string& message) : std::runtime_error(message) {}
};

class ParseError : public RpcError {
public:
    explicit ParseError(const std::string& message) : RpcError("Parse error: " + message) {}
};

class InvalidRequestError : public RpcError {
public:
    explicit InvalidRequestError(const std::string& message) : RpcError("Invalid request: " + message) {}
};

class MethodNotFoundError : public RpcError {
public:
    explicit MethodNotFoundError(const std::string& message) : RpcError("Method not found: " + message) {}
};

class InvalidParamsError : public RpcError {
public:
    explicit InvalidParamsError(const std::string& message) : RpcError("Invalid params: " + message) {}
};

class InternalError : public RpcError {
public:
    explicit InternalError(const std::string& message) : RpcError("Internal error: " + message) {}
};

class ServerError : public RpcError {
public:
    explicit ServerError(const std::string& message) : RpcError("Server error: " + message) {}
};

class ConnectionError : public RpcError {
public:
    explicit ConnectionError(const std::string& message) : RpcError("Connection error: " + message) {}
};

class TimeoutError : public RpcError {
public:
    explicit TimeoutError(const std::string& message) : RpcError("Timeout error: " + message) {}
};

} // namespace zenoh_rpc