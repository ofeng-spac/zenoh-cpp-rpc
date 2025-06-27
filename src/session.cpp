#include "zenoh_rpc/session.hpp"

namespace zenoh_rpc {

Session::Session() : session_(zenoh::Session::open(zenoh::Config())) {
}

Session::Session(zenoh::Config config) : session_(zenoh::Session::open(std::move(config))) {
}

} // namespace zenoh_rpc