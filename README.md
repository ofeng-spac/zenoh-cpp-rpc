# Zenoh C++ RPC

A C++ implementation of JSON-RPC over Zenoh, compatible with the Python zenohrpc library.

## Features

- JSON-RPC 2.0 protocol support
- Built on top of zenoh-cpp
- Compatible with Python zenohrpc
- Simple client-server architecture
- Error handling with custom exception types

## Dependencies

- C++17 compatible compiler
- CMake 3.16+
- zenoh-cpp
- nlohmann/json

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Server Example

```cpp
#include <zenoh_rpc/zenoh_rpc.hpp>

class MyDispatcher : public zenoh_rpc::DispatcherBase {
public:
    MyDispatcher() {
        register_method("echo", [this](const nlohmann::json& params) {
            return params["message"];
        });
    }
};

int main() {
    MyDispatcher dispatcher;
    zenoh_rpc::run_server("example/rpc", dispatcher);
    return 0;
}
```

### Client Example

```cpp
#include <zenoh_rpc/zenoh_rpc.hpp>

int main() {
    zenoh_rpc::Client client("example/rpc");
    
    nlohmann::json params;
    params["message"] = "Hello, World!";
    
    auto result = client.call("echo", params);
    std::cout << "Result: " << result.dump() << std::endl;
    
    return 0;
}
```

## Running Examples

1. Start the server:
```bash
./server_example
```

2. In another terminal, run the client:
```bash
./client_example
```

## API Reference

### DispatcherBase

Base class for implementing RPC method handlers.

- `register_method(name, handler)`: Register a method handler
- `dispatch(method, params)`: Dispatch a method call

### Client

RPC client for calling remote methods.

- `Client(key_expr)`: Create client with key expression
- `call(method, params, timeout)`: Call remote method

### Session

Wrapper around zenoh::Session.

- `Session()`: Create session with default config
- `Session(config)`: Create session with custom config

## Error Handling

The library provides several exception types:

- `RpcError`: Base RPC error
- `ParseError`: JSON parsing error
- `InvalidRequestError`: Invalid request format
- `MethodNotFoundError`: Method not found
- `InvalidParamsError`: Invalid parameters
- `InternalError`: Internal server error
- `ServerError`: Server-side error
- `ConnectionError`: Connection error
- `TimeoutError`: Request timeout

## Compatibility

This C++ implementation is designed to be compatible with the Python zenohrpc library, using the same JSON-RPC protocol and key expressions.