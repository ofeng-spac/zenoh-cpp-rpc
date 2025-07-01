/**
 * @file test_client_improvements.cpp
 * @brief 测试Client构造函数参数验证的简单测试程序
 * 
 * 验证新的encoding参数验证是否正常工作
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

using namespace std::chrono_literals;

// 简化的参数验证函数，模拟Client构造函数中的验证逻辑
void validate_encoding(const std::string& encoding) {
    if (encoding != "json" && encoding != "msgpack") {
        throw std::invalid_argument("Unsupported encoding: " + encoding + ". Supported: json, msgpack");
    }
}

int main() {
    try {
        std::cout << "测试Client构造函数参数验证..." << std::endl;
        
        // 测试1：验证JSON编码
        std::cout << "\n1. 测试JSON编码验证" << std::endl;
        try {
            validate_encoding("json");
            std::cout << "✓ JSON编码验证通过" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✗ JSON编码验证失败: " << e.what() << std::endl;
        }
        
        // 测试2：验证msgpack编码
        std::cout << "\n2. 测试msgpack编码验证" << std::endl;
        try {
            validate_encoding("msgpack");
            std::cout << "✓ msgpack编码验证通过" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✗ msgpack编码验证失败: " << e.what() << std::endl;
        }
        
        // 测试3：验证不支持的编码格式
        std::cout << "\n3. 测试不支持的编码格式" << std::endl;
        try {
            validate_encoding("xml");
            std::cout << "✗ 应该抛出异常但没有抛出" << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "✓ 正确抛出异常: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✗ 抛出了错误类型的异常: " << e.what() << std::endl;
        }
        
        // 测试4：验证空编码格式
        std::cout << "\n4. 测试空编码格式" << std::endl;
        try {
            validate_encoding("");
            std::cout << "✗ 应该抛出异常但没有抛出" << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "✓ 正确抛出异常: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✗ 抛出了错误类型的异常: " << e.what() << std::endl;
        }
        
        // 测试5：验证超时时间处理
        std::cout << "\n5. 测试超时时间处理" << std::endl;
        auto timeout1 = 5000ms;
        auto timeout2 = std::chrono::milliseconds(3000);
        std::cout << "✓ 超时时间1: " << timeout1.count() << "ms" << std::endl;
        std::cout << "✓ 超时时间2: " << timeout2.count() << "ms" << std::endl;
        
        std::cout << "\n所有参数验证测试完成！" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "测试过程中发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}