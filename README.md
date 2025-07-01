# Zenoh C++ RPC

A C++ implementation of JSON-RPC over Zenoh, compatible with the Python zenohrpc library.

## Version 1.2.1 Features

- ✅ **JSON-RPC 2.0 protocol support** with complete error handling
- ✅ **Built on top of zenoh-cpp** with modern C++17 features
- ✅ **Compatible with Python zenohrpc** library
- ✅ **Enhanced error handling** with standard JSON-RPC error codes
- ✅ **Comprehensive Chinese documentation** and code comments
- ✅ **Detailed learning notes** covering C++ advanced concepts
- ✅ **Method registration and dispatch mechanism** with std::function
- ✅ **Lambda expressions and functional programming** patterns
- ✅ **Template programming** with variadic templates and fold expressions

## Core Features

- JSON-RPC 2.0 protocol support
- Built on top of zenoh-cpp
- Compatible with Python zenohrpc
- Simple client-server architecture
- Error handling with custom exception types
- Modern C++17 features and best practices
- Comprehensive documentation and learning materials

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

The library provides several exception types with standard JSON-RPC error codes:

- `ParseError` (-32700): JSON parsing errors
- `InvalidRequestError` (-32600): Invalid request format
- `MethodNotFoundError` (-32601): Method not found
- `InvalidParamsError` (-32602): Invalid parameters
- `InternalError` (-32603): Internal server errors
- `ServerError` (-32000): Server-side errors
- `ConnectionError` (-32001): Connection issues
- `TimeoutError` (-32002): Request timeout

## Documentation

### Learning Notes

This project includes comprehensive learning documentation:

- **LEARNING_NOTES.md**: Detailed C++ concepts and best practices
  - Variadic templates and fold expressions
  - Lambda expressions and functional programming
  - Method registration and dispatch mechanisms
  - std::function and type erasure
  - Modern C++17 features
  - Design patterns (Strategy, Command)
  - Performance considerations

### Development Plan

- **DEVELOPMENT_PLAN.md**: Project roadmap and version history
  - Current status and completed features
  - Future development plans
  - Technical implementation details

## Version History

### v1.2.1 (2024-01)
- ✅ 修复测试文件权限模式问题
- ✅ 完善项目结构和文件组织
- ✅ 优化构建系统和测试流程
- ✅ 提升代码质量和稳定性

### v1.1.0 (2024-01)
- ✅ Enhanced error handling with standard JSON-RPC codes
- ✅ Comprehensive Chinese code comments
- ✅ Complete learning documentation system
- ✅ C++17 modern features implementation
- ✅ Design patterns documentation
- ✅ Performance optimization guidelines

### v1.0.0
- Basic JSON-RPC implementation
- Zenoh integration
- Client-server architecture

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Compatibility

This C++ implementation is designed to be compatible with the Python zenohrpc library, using the same JSON-RPC protocol and key expressions.