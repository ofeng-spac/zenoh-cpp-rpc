#pragma once

#include <zenoh.hxx>
#include <memory>

namespace zenoh_rpc {

class Session {
public:
    Session();
    explicit Session(zenoh::Config config);
    ~Session() = default;

    // Get the underlying zenoh session
    zenoh::Session& get_session() { return session_; }
    const zenoh::Session& get_session() const { return session_; }

    // Declare queryable
    template<typename OnQuery, typename OnDrop = zenoh::closures::none_t>
    auto declare_queryable(const std::string& key_expr, OnQuery&& on_query, OnDrop&& on_drop = zenoh::closures::none) {
        return session_.declare_queryable(key_expr, std::forward<OnQuery>(on_query), std::forward<OnDrop>(on_drop));
    }

    // Declare querier
    auto declare_querier(const std::string& key_expr) {
        return session_.declare_querier(key_expr);
    }

private:
    zenoh::Session session_;
};

} // namespace zenoh_rpc