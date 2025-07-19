#include <iostream>
#include <zenoh.hxx>

int main() {
    std::cout << "Testing Zenoh basic functionality..." << std::endl;
    
    try {
        // 创建一个简单的Zenoh会话测试
        auto config = zenoh::Config::create_default();
        std::cout << "Zenoh config created successfully" << std::endl;
        
        std::cout << "Zenoh basic test completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Zenoh test failed: " << e.what() << std::endl;
        return 1;
    }
}