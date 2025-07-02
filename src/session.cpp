#include "zenoh_rpc/session.hpp"

namespace zenoh_rpc {

/**
 * @brief 默认构造函数
 * 
 * 使用默认配置创建 Zenoh 会话。
 * 会话将使用 Zenoh 的默认网络配置进行初始化。
 */
Session::Session() : session_(zenoh::open(zenoh::Config())), 
                     mode_(SessionMode::PEER), 
                     active_(true) {
    // 使用默认配置创建 Zenoh 会话，默认为 PEER 模式
}

/**
 * @brief 带配置的构造函数
 * @param config Zenoh 配置对象
 * 
 * 使用指定的配置创建 Zenoh 会话。
 * 允许用户自定义网络参数、路由器地址等配置。
 */
Session::Session(const zenoh::Config& config) : session_(zenoh::open(config)), 
                                                mode_(SessionMode::PEER), 
                                                active_(true) {
    // 使用指定配置创建 Zenoh 会话，默认为 PEER 模式
}

Session::Session(SessionMode mode, const std::vector<std::string>& connections) 
    : session_(zenoh::open(create_config(mode, connections))), 
      mode_(mode), 
      connections_(connections), 
      active_(true) {
    // 使用指定模式和连接端点创建 Zenoh 会话
}

Session::~Session() {
    if (active_) {
        close();
    }
}

void Session::close() {
    if (active_) {
        session_.close();
        active_ = false;
    }
}

bool Session::is_active() const {
    return active_;
}

SessionMode Session::get_mode() const {
    return mode_;
}

const std::vector<std::string>& Session::get_connections() const {
    return connections_;
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
zenoh::Querier Session::declare_querier(const std::string& key_expr, uint64_t timeout_ms) {
    zenoh::Session::QuerierOptions options;
    options.timeout_ms = timeout_ms;
    return session_.declare_querier(key_expr, std::move(options));
}

zenoh::Publisher Session::declare_publisher(const std::string& key_expr) {
    return session_.declare_publisher(key_expr);
}

zenoh::Subscriber<void> Session::declare_subscriber(const std::string& key_expr,
                                                    std::function<void(const zenoh::Sample&)> callback) {
    return session_.declare_subscriber(key_expr, std::move(callback));
}

std::string Session::mode_to_string(SessionMode mode) {
    switch (mode) {
        case SessionMode::CLIENT:
            return "client";
        case SessionMode::PEER:
            return "peer";
        case SessionMode::ROUTER:
            return "router";
        default:
            return "peer"; // 默认返回 peer
    }
}

zenoh::Config Session::create_config(SessionMode mode, const std::vector<std::string>& connections) {
    zenoh::Config config;
    
    // 设置会话模式
    std::string mode_str = mode_to_string(mode);
    config.insert_json("mode", "\"" + mode_str + "\"");
    
    // 设置连接端点
    if (!connections.empty()) {
        std::string connect_str = "[";
        for (size_t i = 0; i < connections.size(); ++i) {
            if (i > 0) {
                connect_str += ",";
            }
            connect_str += "\"" + connections[i] + "\"";
        }
        connect_str += "]";
        config.insert_json("connect/endpoints", connect_str);
    }
    
    return config;
}

} // namespace zenoh_rpc