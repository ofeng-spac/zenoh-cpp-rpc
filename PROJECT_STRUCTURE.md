# Zenoh C++ RPC 项目结构说明

## 目录结构

```
zenoh-cpp-rpc/
├── bin/                    # 编译后的可执行文件
├── docs/                   # 项目文档
│   ├── SESSION_MANAGEMENT.md
│   ├── DEVELOPMENT_PLAN.md
│   ├── LEARNING_NOTES.md
│   ├── ZENOH_CPP_RPC_COMPLETE_FIX_GUIDE.md
│   └── git_commands.md
├── examples/               # 示例代码
│   ├── client_example.cpp
│   ├── server_example.cpp
│   └── session_management_example.cpp
├── include/                # 头文件
│   └── zenoh_rpc/
│       ├── errors.hpp
│       ├── jsonrpc_client.hpp
│       ├── jsonrpc_proto.hpp
│       ├── jsonrpc_server.hpp
│       ├── session.hpp
│       └── zenoh_rpc.hpp
├── src/                    # 源文件
│   ├── errors.cpp
│   ├── jsonrpc_client.cpp
│   ├── jsonrpc_proto.cpp
│   ├── jsonrpc_server.cpp
│   └── session.cpp
├── tests/                  # 测试文件
│   ├── test_client_improvements.cpp
│   ├── test_client_msgpack.cpp
│   ├── test_error_handling.cpp
│   ├── test_jsonrpc.cpp
│   ├── test_msgpack_support.cpp
│   ├── test_parameter_handling.cpp
│   ├── test_query_communication.cpp
│   └── test_zenoh.cpp
├── tools/                  # 工具程序
│   ├── simple_client.cpp
│   ├── simple_query_client.cpp
│   ├── simple_query_server.cpp
│   └── simple_server.cpp
├── CMakeLists.txt          # CMake 构建配置
├── Makefile               # 生成的 Makefile
├── README.md              # 项目说明
└── .gitignore             # Git 忽略文件
```

## 目录说明

### `/bin/`
存放所有编译后的可执行文件，包括示例程序、工具程序和测试程序。

### `/docs/`
项目相关文档，包括：
- 开发计划
- 学习笔记
- 修复指南
- 会话管理文档
- Git 命令参考

### `/examples/`
示例代码，展示如何使用 Zenoh RPC 库：
- `client_example.cpp`: 客户端示例
- `server_example.cpp`: 服务器示例
- `session_management_example.cpp`: 会话管理示例

### `/include/zenoh_rpc/`
库的头文件，定义了 RPC 相关的接口和类。

### `/src/`
库的实现源文件。

### `/tests/`
各种测试程序，用于验证库的功能和性能。

### `/tools/`
实用工具程序，包括简单的客户端和服务器实现。

## 构建说明

1. 编译项目：
   ```bash
   make
   ```

2. 运行示例：
   ```bash
   ./bin/server_example    # 启动服务器
   ./bin/client_example    # 启动客户端
   ```

3. 运行测试：
   ```bash
   ./bin/test_jsonrpc      # 运行 JSON-RPC 测试
   ./bin/test_zenoh        # 运行 Zenoh 测试
   ```

4. 使用工具：
   ```bash
   ./bin/simple_query_server    # 启动简单查询服务器
   ./bin/simple_query_client    # 启动简单查询客户端
   ```

## 重构说明

本次重构主要目标：
1. **分离关注点**：将示例、测试、工具和文档分别放在不同目录
2. **清理根目录**：移除根目录中的可执行文件和临时文件
3. **统一输出**：所有可执行文件统一输出到 `bin/` 目录
4. **改进构建**：更新 CMakeLists.txt 以支持新的目录结构
5. **文档整理**：将所有文档集中到 `docs/` 目录

这样的结构更加清晰，便于维护和开发。