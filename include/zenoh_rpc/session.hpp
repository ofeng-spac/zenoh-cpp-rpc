#pragma once

#include <zenoh.hxx>

namespace zenoh_rpc {

/**
 * @file session.hpp
 * @brief Zenoh 会话管理
 * 
 * 本文件定义了 Zenoh 会话的封装类，提供了：
 * - Zenoh 会话的创建和管理
 * - 可查询对象（Queryable）的声明
 * - 查询器（Querier）的声明
 * - 底层 Zenoh 会话的访问接口
 */

/**
 * @class Session
 * @brief Zenoh 会话封装类
 * 
 * 提供对 Zenoh 会话的高级封装，简化 RPC 客户端和服务器的会话管理。
 * 支持默认配置和自定义配置的会话创建。
 */
class Session {
public:
    /**
     * @brief 默认构造函数
     * 
     * 使用默认配置创建 Zenoh 会话。
     * 会话将使用 Zenoh 的默认网络配置进行初始化。
     */
    Session();
    
    /**
     * @brief 带配置的构造函数
     * @param config Zenoh 配置对象
     * 
     * 使用指定的配置创建 Zenoh 会话。
     * 允许用户自定义网络参数、路由器地址等配置。
     */
    explicit Session(const zenoh::Config& config);
    
    /**
     * @brief 获取底层 Zenoh 会话引用
     * @return Zenoh 会话的引用
     * 
     * 提供对底层 Zenoh 会话的直接访问，
     * 用于需要使用原生 Zenoh API 的高级操作。
     */
    zenoh::Session& get_session();
    
    /**
     * @brief 声明可查询对象
     * @param key_expr 键表达式，定义查询的范围
     * @param callback 查询处理回调函数
     * @return 可查询对象
     * 
     * 在指定的键表达式上注册一个可查询对象，
     * 当有匹配的查询请求时，会调用提供的回调函数。
     * 主要用于 RPC 服务器端接收和处理客户端请求。
     */
    zenoh::Queryable<void> declare_queryable(const std::string& key_expr, 
                                              std::function<void(const zenoh::Query&)> callback);
    
    /**
     * @brief 声明查询器
     * @param key_expr 键表达式，定义查询的目标
     * @return 查询器对象
     * 
     * 创建一个查询器，用于向指定键表达式发送查询请求。
     * 主要用于 RPC 客户端向服务器发送方法调用请求。
     */
    zenoh::Querier declare_querier(const std::string& key_expr);
    
private:
    /// 底层 Zenoh 会话对象
    zenoh::Session session_;
};

} // namespace zenoh_rpc