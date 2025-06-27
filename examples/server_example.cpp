#include <iostream>
#include <zenoh_rpc/zenoh_rpc.hpp>

using namespace zenoh_rpc;
using json = nlohmann::json;

class ExampleDispatcher : public DispatcherBase {
public:
    ExampleDispatcher() {
        // Register echo method
        register_method("echo", [this](const json& params) -> json {
            return this->echo(params);
        });
        
        // Register sum method
        register_method("sum", [this](const json& params) -> json {
            return this->sum(params);
        });
    }
    
private:
    json echo(const json& params) {
        std::cout << "Echo method called with params: " << params.dump() << std::endl;
        
        if (!params.contains("message")) {
            throw InvalidParamsError("Missing 'message' parameter");
        }
        
        return params["message"];
    }
    
    json sum(const json& params) {
        std::cout << "Sum method called with params: " << params.dump() << std::endl;
        
        if (!params.contains("a") || !params.contains("b")) {
            throw InvalidParamsError("Missing 'a' or 'b' parameter");
        }
        
        if (!params["a"].is_number() || !params["b"].is_number()) {
            throw InvalidParamsError("Parameters 'a' and 'b' must be numbers");
        }
        
        double a = params["a"];
        double b = params["b"];
        
        return a + b;
    }
};

int main() {
    try {
        ExampleDispatcher dispatcher;
        run_server("example/rpc", dispatcher);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}