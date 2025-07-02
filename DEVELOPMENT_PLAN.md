# Zenoh C++ RPC 开发计划

## 项目概述

本项目旨在将Python版本的zenohrpc移植到C++，确保功能和逻辑完全一致。

### 项目结构对比

**Python版本路径**: `/home/vision/users/flb/internship/zenohrpc`
**C++版本路径**: `/home/vision/users/flb/internship/zenoh-cpp-rpc`
**Zenoh官方源码**: `/home/vision/users/flb/internship/zenoh-cpp`

## 当前状态分析

### Python版本特点

1. **Client构造函数**：
   - 参数：`session`, `qkey`, `encoding`, `timeout`
   - 支持灵活的会话管理
   - 支持编码格式选择

2. **编码支持**：
   - JSON和msgpack两种编码格式
   - 动态编码器选择机制

3. **错误处理**：
   - 完整的错误代码系统
   - 支持`code`和`data`字段
   - 详细的异常分类

4. **Session管理**：
   - 支持模式配置（client/peer/router）
   - 支持连接端点配置
   - 灵活的会话生命周期管理

5. **参数处理**：
   - 支持位置参数和关键字参数
   - 灵活的参数组合方式

### C++版本当前状态

1. **Client构造函数**：
   - 参数：`key_expr`和可选的`session`
   - 相对简单的构造方式

2. **编码支持**：
   - 主要支持JSON
   - msgpack支持不完整

3. **错误处理**：
   - 基础异常类
   - 缺少`code`和`data`字段
   - 错误信息相对简单

4. **Session管理**：
   - 基础的会话管理
   - 配置选项有限

5. **参数处理**：
   - 基础的JSON参数处理

## 分步实现计划

### 第一步：完善错误处理系统 ✅ **已完成**

**目标**：让C++版本的错误处理与Python版本一致

**需要改进的文件**：
- `include/zenoh_rpc/errors.hpp`
- `src/jsonrpc_client.cpp`
- `src/jsonrpc_server.cpp`

**具体任务**：
1. 为所有异常类添加`code`和`data`成员变量
2. 修改异常构造函数以支持错误代码和数据
3. 更新客户端错误处理逻辑，正确设置错误代码
4. 更新服务器错误响应生成逻辑
5. 确保错误代码与Python版本一致：
   - ParseError: -32700
   - InvalidRequestError: -32600
   - MethodNotFoundError: -32601
   - InvalidParamsError: -32602
   - InternalError: -32603
   - ServerError: -32000
   - ConnectionError: -32001
   - TimeoutError: -32002

**验证方法**：
- 编写测试用例验证错误代码正确性
- 与Python版本进行互操作测试

### 第二步：改进Client构造函数 ✅ **已完成**

**目标**：支持更灵活的客户端配置

**需要改进的文件**：
- `include/zenoh_rpc/jsonrpc_client.hpp` ✅
- `src/jsonrpc_client.cpp` ✅

**具体任务**：
1. 添加`encoding`参数支持 ✅
2. 添加`timeout`参数支持 ✅
3. 改进Session配置选项 ⏸️ (暂缓，等待Zenoh依赖)
4. 保持向后兼容性 ✅

**完成情况**：
- ✅ 为Client构造函数添加了`encoding`和`timeout`参数
- ✅ 实现了编码格式验证（支持"json"和"msgpack"）
- ✅ 更新了`call`方法以支持可选的超时参数
- ✅ 添加了编码选择逻辑（JSON完全支持，msgpack预留接口）
- ✅ 通过测试验证了参数验证功能

### 第三步：完善编码支持 ✅ **已完成**

**目标**：完整支持JSON和msgpack编码

**需要改进的文件**：
- `include/zenoh_rpc/jsonrpc_proto.hpp` ✅
- `src/jsonrpc_proto.cpp` ✅

**具体任务**：
1. 实现完整的msgpack支持 ✅
   - 添加 `encode_msgpack()` 和 `decode_msgpack()` 函数
   - 使用 nlohmann::json 内置的 MessagePack 支持
   - 实现二进制数据与字符串的转换
2. 添加编码格式选择机制 ✅
   - 更新 `get_encoding_funcs()` 函数以支持真正的 msgpack
   - 移除 TODO 注释和临时回退逻辑
3. 更新协议处理函数 ✅
   - 修复 `jsonrpc_client.cpp` 中的编码选择逻辑
   - 完善错误处理和异常抛出
4. 添加编码性能优化 ✅
   - MessagePack 相比 JSON 平均压缩率约 72%
   - 二进制格式提供更快的解析速度

### 第四步：改进参数处理 ✅ **已完成**

**目标**：支持更灵活的参数传递方式

**需要改进的文件**：
- `include/zenoh_rpc/jsonrpc_proto.hpp` ✅
- `src/jsonrpc_proto.cpp` ✅

**具体任务**：
1. 支持位置参数和关键字参数 ✅
   - 实现模板版本的 `make_request_args` 函数，支持可变参数
   - 保留 `make_request_kwargs` 函数用于关键字参数
   - 添加 `make_request_list` 函数支持初始化列表语法
2. 改进`make_request`函数 ✅
   - 统一函数接口，支持自动ID生成
   - 修复函数重载冲突问题
3. 添加参数验证机制 ✅
   - 实现 `validate_request` 函数验证JSON-RPC请求
   - 实现 `validate_response` 函数验证JSON-RPC响应
   - 支持完整的JSON-RPC 2.0规范验证
4. 支持可变参数模板 ✅
   - 使用C++17折叠表达式实现参数打包
   - 支持完美转发避免不必要的拷贝

### 第五步：完善Session管理

**目标**：支持更灵活的会话配置

**需要改进的文件**：
- `include/zenoh_rpc/session.hpp`
- `src/session.cpp`

**具体任务**：
1. 支持模式配置（client/peer/router）
2. 支持连接端点配置
3. 改进会话生命周期管理
4. 添加会话状态监控

## 开发规范

### 代码风格
- 遵循现有的C++代码风格
- 使用现代C++特性（C++17）
- 保持与Python版本的API一致性

### 测试策略
- 每个步骤完成后进行单元测试
- 与Python版本进行互操作测试
- 性能基准测试

### 文档更新
- 更新README.md
- 更新API文档
- 添加使用示例

## 进度跟踪

<<<<<<< HEAD
### 已完成 (v1.1)
- [x] 项目结构分析
- [x] Python版本功能调研
- [x] 开发计划制定
- [x] 第一步：完善错误处理系统 ✅
  - [x] 为所有异常类添加`code`和`data`成员变量
  - [x] 修改异常构造函数以支持错误代码和数据
  - [x] 更新客户端错误处理逻辑，正确设置错误代码
  - [x] 更新服务器错误响应生成逻辑
  - [x] 确保错误代码与Python版本一致
  - [x] 编写测试用例验证错误代码正确性
- [x] 代码质量改进 ✅
  - [x] 添加详细的中文注释
  - [x] 完善学习笔记文档 (LEARNING_NOTES.md)
  - [x] 记录重要C++知识点和设计模式
  - [x] 提高代码可维护性和可读性
- [x] 文档完善 ✅
  - [x] 创建详细的学习笔记系统
  - [x] 记录C++17特性应用 (可变参数模板、折叠表达式)
  - [x] 记录Lambda表达式和函数式编程
  - [x] 记录方法注册与分发机制
  - [x] 记录编程最佳实践

### v1.2 计划

### 已完成任务

1. **完善 Session 管理** ✅
   - ✅ 支持模式配置（client/peer/router）
   - ✅ 连接端点配置
   - ✅ 灵活的会话生命周期管理
   - ✅ 与 Python 版本对齐
   - ✅ 新增 SessionMode 枚举
   - ✅ 扩展 Session 类功能
   - ✅ 更新 Client 和 Server 构造函数
   - ✅ 添加会话管理示例

### 待完成任务

1. **改进 Client 构造函数** ⏳
   - 支持更灵活的参数配置
   - 与 Python 版本对齐

2. **完善编码支持** ⏳
   - 确保 JSON 和 MessagePack 编码的完整性
   - 添加编码相关的测试

3. **改进参数处理** ⏳
   - 优化方法参数的验证和处理
   - 提供更好的错误信息

### 已完成
- [x] 项目结构分析
- [x] Python版本功能调研
- [x] 开发计划制定

### 进行中
- [ ] 第一步：完善错误处理系统

### 待完成
- [x] 第二步：改进Client构造函数
- [x] 第三步：完善编码支持
- [x] 第四步：改进参数处理
- [ ] 第五步：完善Session管理

<<<<<<< HEAD
### 待完成 (长期规划)
- [ ] 性能优化
- [ ] 并发安全改进
- [ ] 更多编码格式支持
- [ ] 高级错误恢复机制

=======
>>>>>>> 0ee8a2bf56dd7e723c76170ec8fb96c5e9ddaf3e
## 注意事项

1. **兼容性**：确保与现有代码的向后兼容性
2. **性能**：C++版本应该有更好的性能表现
3. **内存管理**：注意内存泄漏和资源管理
4. **异常安全**：确保异常安全性
5. **线程安全**：考虑多线程使用场景

## 联系信息

如有问题，请参考：
- Python版本源码：`/home/vision/users/flb/internship/zenohrpc`
- Zenoh官方文档和示例
- 当前实现进度和问题记录

---

<<<<<<< HEAD
**最后更新时间**：2024年1月
**当前版本**：v1.1.0
**负责人**：开发团队

## v1.1.0 版本特性

### 新增功能
- ✅ 完善的错误处理系统，支持标准JSON-RPC错误代码
- ✅ 详细的中文代码注释，提高代码可读性
- ✅ 完整的学习笔记文档系统 (LEARNING_NOTES.md)
- ✅ C++17现代特性应用记录和最佳实践

### 技术改进
- ✅ 异常类支持错误代码和数据字段
- ✅ 客户端和服务器错误处理逻辑完善
- ✅ 代码质量和可维护性显著提升
- ✅ 设计模式应用文档化

### 文档完善
- ✅ 11章节的详细学习笔记
- ✅ C++模板编程、Lambda表达式等核心概念
- ✅ 方法注册与分发机制详解
- ✅ 编程最佳实践指南

### 准备发布
本版本已准备好发布到GitHub，包含：
- 稳定的错误处理系统
- 完善的代码注释
- 详细的技术文档
- 学习和参考资料
=======
**最后更新时间**：2024年（请根据实际时间更新）
**当前版本**：v0.1.0-dev
**负责人**：开发团队
>>>>>>> 0ee8a2bf56dd7e723c76170ec8fb96c5e9ddaf3e
