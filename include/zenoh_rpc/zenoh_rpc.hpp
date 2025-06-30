#pragma once

/**
 * @file zenoh_rpc.hpp
 * @brief Zenoh RPC 库主头文件
 * 
 * 这是 Zenoh RPC 库的主要包含文件，提供了完整的 JSON-RPC over Zenoh 功能。
 * 通过包含此文件，用户可以访问库的所有核心组件。
 * 
 * 主要组件：
 * - 错误处理系统 (errors.hpp)
 * - JSON-RPC 协议实现 (jsonrpc_proto.hpp)
 * - RPC 客户端 (jsonrpc_client.hpp)
 * - RPC 服务器 (jsonrpc_server.hpp)
 * - Zenoh 会话管理 (session.hpp)
 * 
 * 使用示例：
 * @code
 * #include <zenoh_rpc/zenoh_rpc.hpp>
 * 
 * // 创建客户端
 * zenoh_rpc::Client client("example/service");
 * 
 * // 调用远程方法
 * auto result = client.call("add", {1, 2});
 * @endcode
 */

#include "errors.hpp"
#include "jsonrpc_proto.hpp"
#include "jsonrpc_client.hpp"
#include "jsonrpc_server.hpp"
#include "session.hpp"