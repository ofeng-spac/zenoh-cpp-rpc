# Session 管理功能指南

本文档介绍 zenoh-cpp-rpc 库中完善的 Session 管理功能，包括会话模式配置、连接端点设置和生命周期管理。

## 概述

Session 管理是 v1.2 版本的重要改进，旨在与 Python 版本的功能对齐，提供更灵活和强大的会话控制能力。

## 主要特性

### 1. 会话模式支持

支持三种 Zenoh 会话模式：

- **CLIENT**: 客户端模式，连接到路由器
- **PEER**: 对等模式，可以直接与其他对等节点通信
- **ROUTER**: 路由器模式，作为网络中的路由节点

```cpp
#include "zenoh_rpc/session.hpp"

using namespace zenoh_rpc;

// 创建不同模式的会话
Session client_session(SessionMode::CLIENT);
Session peer_session(SessionMode::PEER);
Session router_session(SessionMode::ROUTER);
```

### 2. 连接端点配置

可以指定连接到特定的 Zenoh 端点：

```cpp
// 配置连接端点
std::vector<std::string> endpoints = {
    "tcp/127.0.0.1:7447",
    "tcp/localhost:7448"
};

// 创建带连接端点的会话
Session session(SessionMode::CLIENT, endpoints);
```

### 3. 会话生命周期管理

提供完整的会话生命周期控制：

```cpp
Session session(SessionMode::PEER);

// 检查会话状态
if (session.is_active()) {
    std::cout << "会话处于活动状态" << std::endl;
}

// 获取会话信息
SessionMode mode = session.get_mode();
const auto& connections = session.get_connections();

// 手动关闭会话
session.close();

// 会话也会在析构时自动关闭
```

## Session 类 API

### 构造函数

```cpp
// 默认构造函数（PEER 模式）
Session();

// 使用 Zenoh 配置
Session(const zenoh::Config& config);

// 指定模式和连接端点
Session(SessionMode mode, const std::vector<std::string>& connections = {});
```

### 主要方法

```cpp
// 生命周期管理
void close();                                    // 关闭会话
bool is_active() const;                         // 检查会话状态

// 会话信息
SessionMode get_mode() const;                   // 获取会话模式
const std::vector<std::string>& get_connections() const; // 获取连接端点

// Zenoh 对象声明
zenoh::Queryable<void> declare_queryable(const std::string& key_expr, 
                                          std::function<void(const zenoh::Query&)> callback);
zenoh::Querier declare_querier(const std::string& key_expr);
zenoh::Publisher declare_publisher(const std::string& key_expr);
zenoh::Subscriber<void> declare_subscriber(const std::string& key_expr,
                                           std::function<void(const zenoh::Sample&)> callback);

// 底层访问
zenoh::Session& get_session();                  // 获取底层 Zenoh 会话
```

## 客户端集成

### 基本用法

```cpp
#include "zenoh_rpc/jsonrpc_client.hpp"

using namespace zenoh_rpc;

// 使用默认配置
Client client("example/service");

// 指定编码和超时
Client client("example/service", "json", std::chrono::milliseconds(3000));
```

### 高级配置

```cpp
// 指定会话模式和连接端点
std::vector<std::string> endpoints = {"tcp/127.0.0.1:7447"};
Client client("example/service", SessionMode::CLIENT, endpoints);

// 使用共享会话
Session shared_session(SessionMode::PEER);
Client client1("service1", shared_session);
Client client2("service2", shared_session);
```

## 服务器集成

### 基本用法

```cpp
#include "zenoh_rpc/jsonrpc_server.hpp"

using namespace zenoh_rpc;

class MyDispatcher : public DispatcherBase {
public:
    MyDispatcher() {
        register_method("add", [](const json& params) -> json {
            return params[0].get<double>() + params[1].get<double>();
        });
    }
};

MyDispatcher dispatcher;

// 使用默认配置
run_server("example/service", dispatcher);
```

### 高级配置

```cpp
// 指定会话模式
run_server("example/service", dispatcher, SessionMode::PEER);

// 指定会话模式和连接端点
std::vector<std::string> endpoints = {"tcp/127.0.0.1:7447"};
run_server("example/service", dispatcher, SessionMode::CLIENT, endpoints);

// 使用共享会话
Session shared_session(SessionMode::ROUTER);
run_server("example/service", dispatcher, shared_session);
```

## 最佳实践

### 1. 会话模式选择

- **CLIENT**: 适用于简单的客户端应用，需要连接到中央路由器
- **PEER**: 适用于分布式应用，节点间直接通信
- **ROUTER**: 适用于作为网络中心节点的应用

### 2. 连接端点配置

```cpp
// 生产环境：指定具体的路由器地址
std::vector<std::string> prod_endpoints = {
    "tcp/router1.example.com:7447",
    "tcp/router2.example.com:7447"
};

// 开发环境：使用本地路由器
std::vector<std::string> dev_endpoints = {
    "tcp/127.0.0.1:7447"
};
```

### 3. 会话共享

```cpp
// 在多个客户端间共享会话以节省资源
Session shared_session(SessionMode::CLIENT, endpoints);

Client service1_client("service1", shared_session);
Client service2_client("service2", shared_session);
Client service3_client("service3", shared_session);
```

### 4. 错误处理

```cpp
try {
    Session session(SessionMode::CLIENT, endpoints);
    Client client("example/service", session);
    
    auto result = client.call("method", {"param1", "param2"});
    
} catch (const ConnectionError& e) {
    std::cerr << "连接错误: " << e.what() << std::endl;
} catch (const TimeoutError& e) {
    std::cerr << "超时错误: " << e.what() << std::endl;
}
```

## 与 Python 版本的对比

| 功能 | Python 版本 | C++ 版本 |
|------|-------------|----------|
| 会话模式 | ✅ | ✅ |
| 连接端点 | ✅ | ✅ |
| 生命周期管理 | ✅ | ✅ |
| 共享会话 | ✅ | ✅ |
| 自动析构 | ✅ | ✅ |

## 示例代码

完整的示例代码请参考：
- `examples/session_management_example.cpp` - Session 管理功能演示
- `examples/basic_example.cpp` - 基本 RPC 使用示例
- `examples/advanced_example.cpp` - 高级功能示例

## 注意事项

1. **线程安全**: Session 对象不是线程安全的，在多线程环境中需要适当的同步机制
2. **资源管理**: 会话会在析构时自动关闭，但建议在不需要时主动调用 `close()`
3. **网络配置**: 确保指定的连接端点可达，否则会话创建可能失败
4. **模式兼容性**: 不同模式的会话可能有不同的网络行为，请根据应用需求选择合适的模式

## 故障排除

### 常见问题

1. **会话创建失败**
   - 检查网络连接
   - 验证端点地址格式
   - 确认 Zenoh 路由器运行状态

2. **连接超时**
   - 增加超时时间
   - 检查防火墙设置
   - 验证端点可达性

3. **资源泄漏**
   - 确保会话正确关闭
   - 检查异常处理逻辑
   - 使用 RAII 模式管理资源

更多详细信息请参考项目文档和示例代码。