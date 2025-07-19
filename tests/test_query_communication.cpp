#include <zenoh.hxx>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

using namespace zenoh;
using namespace std::chrono_literals;

struct TestCase {
    std::string name;
    std::string keyexpr;
    std::string payload;
};

int main(int argc, char **argv) {
    Config config = Config::create_default();
    if (argc > 1) {
        config = Config::from_file(argv[1]);
    } else {
        // 配置为client模式，连接到zenohd路由器
        config.insert_json5("mode", "\"client\"");
        config.insert_json5("connect/endpoints", "[\"tcp/127.0.0.1:7449\"]");
        std::cout << "使用默认配置：连接到 zenohd 路由器 127.0.0.1:7449" << std::endl;
    }

    std::cout << "正在打开会话..." << std::endl;
    auto session = Session::open(std::move(config));

    std::cout << "自动测试Query客户端已启动" << std::endl;
    
    // 定义测试用例
    std::vector<TestCase> test_cases = {
        {"默认查询", "rpc/example/queryable", ""},
        {"Echo查询", "rpc/example/echo", "Hello from automated test!"},
        {"时间查询", "rpc/example/time", ""}
    };
    
    // 等待服务器准备就绪
    std::cout << "等待服务器准备就绪..." << std::endl;
    std::this_thread::sleep_for(2s);
    
    for (const auto& test_case : test_cases) {
        std::cout << "\n=== 测试 " << test_case.name << " ===" << std::endl;
        
        // 发送查询
        std::mutex m;
        std::condition_variable done_signal;
        bool done = false;
        int reply_count = 0;
        
        auto on_reply = [&reply_count, &test_case](const Reply &reply) {
            reply_count++;
            if (reply.is_ok()) {
                const auto &sample = reply.get_ok();
                std::cout << "[" << test_case.name << "] 收到响应 #" << reply_count << " ('" 
                          << sample.get_keyexpr().as_string_view() << "' : '" 
                          << sample.get_payload().as_string() << "')" << std::endl;
            } else {
                std::cout << "[" << test_case.name << "] 收到错误: " << reply.get_err().get_payload().as_string() << std::endl;
            }
        };
        
        auto on_done = [&m, &done, &done_signal]() {
            std::lock_guard lock(m);
            done = true;
            done_signal.notify_all();
        };
        
        Session::GetOptions options;
        options.target = QueryTarget::Z_QUERY_TARGET_BEST_MATCHING;
        options.timeout_ms = 3000; // 3秒超时
        if (!test_case.payload.empty()) {
            options.payload = test_case.payload;
        }
        
        std::cout << "发送查询到 '" << test_case.keyexpr << "'";
        if (!test_case.payload.empty()) {
            std::cout << " 携带数据: '" << test_case.payload << "'";
        }
        std::cout << "..." << std::endl;
        
        session.get(test_case.keyexpr, "", on_reply, on_done, std::move(options));
        
        // 等待查询完成
        std::unique_lock lock(m);
        if (done_signal.wait_for(lock, 4s, [&done] { return done; })) {
            std::cout << "[" << test_case.name << "] 查询完成，共收到 " << reply_count << " 个响应" << std::endl;
        } else {
            std::cout << "[" << test_case.name << "] 查询超时" << std::endl;
        }
        
        // 测试间隔
        std::this_thread::sleep_for(1s);
    }
    
    std::cout << "\n=== 所有测试完成 ===" << std::endl;
    
    return 0;
}