#pragma once

#include <zenoh.hxx>
#include <string>
#include <vector>

namespace zenoh_rpc {

/**
 * @file session.hpp
 * @brief Zenoh 会话管理
 * 
 * 本文件定义了 Zenoh 会话的封装类，提供了：
 * - Zenoh 会话的创建和管理
 * - 模式配置（client/peer/router）
 * - 连接端点配置
 * - 可查询对象（Queryable）的声明
 * - 查询器（Querier）的声明
 * - 底层 Zenoh 会话的访问接口
 */

/**
 * @enum SessionMode
 * @brief Zenoh 会话模式枚举
 * 
 * 定义了 Zenoh 会话的三种运行模式：
 * - CLIENT: 客户端模式，连接到路由器或对等节点
 * - PEER: 对等节点模式，可以直接与其他对等节点通信
 * - ROUTER: 路由器模式，作为网络中的路由节点
 */
enum class SessionMode {
    CLIENT,  ///< 客户端模式
    PEER,    ///< 对等节点模式
    ROUTER   ///< 路由器模式
};

/**
 * @class Session
 * @brief Zenoh 会话封装类
 * 
 * 提供对 Zenoh 会话的高级封装，简化 RPC 客户端和服务器的会话管理。
 * 支持默认配置、模式配置和连接端点配置的会话创建。
 */
class Session {
public:
    /**
     * @brief 默认构造函数
     * 
     * 使用默认配置创建 Zenoh 会话。
     * 默认使用客户端模式，连接到本地路由器 tcp/127.0.0.1:7447。
     */
    Session();
    
    /**
     * @brief 带模式和连接端点的构造函数
     * @param mode 会话模式（client/peer/router）
     * @param connections 连接端点列表
     * 
     * 使用指定的模式和连接端点创建 Zenoh 会话。
     * 这是推荐的构造方式，提供了最大的灵活性。
     */
    Session(SessionMode mode, const std::vector<std::string>& connections = {"tcp/127.0.0.1:7447"});
    
    /**
     * @brief 带配置的构造函数
     * @param config Zenoh 配置对象
     * 
     * 使用指定的配置创建 Zenoh 会话。
     * 允许用户自定义网络参数、路由器地址等配置。
     */
    explicit Session(const zenoh::Config& config);
    
    /**
     * @brief 析构函数
     * 
     * 自动关闭 Zenoh 会话，释放相关资源。
     */
    ~Session();
    
    /**
     * @brief 手动关闭会话
     * 
     * 显式关闭 Zenoh 会话，释放网络连接和相关资源。
     * 调用此方法后，会话将不再可用。
     */
    void close();
    
    /**
     * @brief 检查会话是否处于活动状态
     * @return 如果会话活动返回 true，否则返回 false
     * 
     * 用于检查会话的当前状态，确保在使用前会话是有效的。
     */
    bool is_active() const;
    
    /**
     * @brief 获取会话模式
     * @return 当前会话的模式
     * 
     * 返回会话创建时设置的模式（client/peer/router）。
     */
    SessionMode get_mode() const;
    
    /**
     * @brief 获取连接端点列表
     * @return 连接端点的字符串向量
     * 
     * 返回会话创建时配置的连接端点列表。
     */
    const std::vector<std::string>& get_connections() const;
    
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
     * @param timeout_ms 查询超时时间（毫秒）
     * @return 查询器对象
     * 
     * 创建一个查询器，用于向指定键表达式发送查询请求。
     * 主要用于 RPC 客户端向服务器发送方法调用请求。
     */
    zenoh::Querier declare_querier(const std::string& key_expr, uint64_t timeout_ms = 0);
    
    /**
     * @brief 声明发布者
     * @param key_expr 键表达式，定义发布的主题
     * @return 发布者对象
     * 
     * 创建一个发布者，用于向指定键表达式发布数据。
     * 主要用于发布/订阅模式的数据传输。
     */
    zenoh::Publisher declare_publisher(const std::string& key_expr);
    
    /**
     * @brief 声明订阅者
     * @param key_expr 键表达式，定义订阅的主题
     * @param callback 数据接收回调函数
     * @return 订阅者对象
     * 
     * 创建一个订阅者，用于订阅指定键表达式的数据。
     * 当有匹配的数据发布时，会调用提供的回调函数。
     */
    zenoh::Subscriber<void> declare_subscriber(const std::string& key_expr,
                                               std::function<void(const zenoh::Sample&)> callback);
    
private:
    /**
     * @brief 将 SessionMode 枚举转换为字符串
     * @param mode 会话模式枚举值
     * @return 对应的字符串表示
     */
    static std::string mode_to_string(SessionMode mode);
    
    /**
     * @brief 创建带有模式和连接配置的 Zenoh 配置对象
     * @param mode 会话模式
     * @param connections 连接端点列表
     * @return 配置好的 Zenoh 配置对象
     */
    static zenoh::Config create_config(SessionMode mode, const std::vector<std::string>& connections);
    
private:
    /// 底层 Zenoh 会话对象
    zenoh::Session session_;
    /// 会话模式
    SessionMode mode_;
    /// 连接端点列表
    std::vector<std::string> connections_;
    /// 会话是否处于活动状态
    bool active_;
};

} // namespace zenoh_rpc