#include "zenoh_rpc/session.hpp"

namespace zenoh_rpc {

/**
 * @brief 默认构造函数
 * 
 * 使用默认配置创建 Zenoh 会话。
 * 会话将使用 Zenoh 的默认网络配置进行初始化。
 */
Session::Session() : session_(zenoh::open(zenoh::Config())) {
}

/**
 * @brief 带配置的构造函数
 * @param config Zenoh 配置对象
 * 
 * 使用指定的配置创建 Zenoh 会话。
 * 允许用户自定义网络参数、路由器地址等配置。
 */
Session::Session(const zenoh::Config& config) : session_(zenoh::open(config)) {
}

/**
 * @brief 获取底层 Zenoh 会话引用
 * @return Zenoh 会话的引用
 * 
 * 提供对底层 Zenoh 会话的直接访问，
 * 用于需要使用原生 Zenoh API 的高级操作。
 */
zenoh::Session& Session::get_session() {
    return session_;
}

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
zenoh::Queryable<void> Session::declare_queryable(const std::string& key_expr, 
                                                  std::function<void(const zenoh::Query&)> callback) {
    return session_.declare_queryable(key_expr, callback);
}

/**
 * @brief 声明查询器
 * @param key_expr 键表达式，定义查询的目标
 * @return 查询器对象
 * 
 * 创建一个查询器，用于向指定键表达式发送查询请求。
 * 主要用于 RPC 客户端向服务器发送方法调用请求。
 */
zenoh::Querier Session::declare_querier(const std::string& key_expr) {
    return session_.declare_querier(key_expr);
}

} // namespace zenoh_rpc