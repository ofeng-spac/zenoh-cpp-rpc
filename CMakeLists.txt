cmake_minimum_required(VERSION 3.16)
project(zenoh_rpc VERSION 1.2.1 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译定义以启用不稳定特性
#add_compile_definitions(Z_FEATURE_UNSTABLE_API)

# Find required packages
find_package(PkgConfig REQUIRED)

# First find zenohc to ensure zenohc::lib target is available
find_package(zenohc QUIET)

# Try to find zenohcxx
find_package(zenohcxx QUIET)
if(zenohcxx_FOUND)
    set(HEADER_ONLY_BUILD OFF)
    message(STATUS "Found zenohcxx, building with full Zenoh support")
else()
    # Try to find zenohcxx in common installation paths
    find_path(ZENOHCXX_INCLUDE_DIR zenoh.hxx
        PATHS /usr/local/include /opt/zenoh/include
        PATH_SUFFIXES zenohcxx)
    find_library(ZENOHCXX_LIBRARY zenohcxx
        PATHS /usr/local/lib /opt/zenoh/lib)
    
    if(ZENOHCXX_INCLUDE_DIR AND ZENOHCXX_LIBRARY)
        set(HEADER_ONLY_BUILD OFF)
        message(STATUS "Found zenohcxx manually, building with full Zenoh support")
        # Create imported target
        add_library(zenohcxx::lib UNKNOWN IMPORTED)
        set_target_properties(zenohcxx::lib PROPERTIES
            IMPORTED_LOCATION ${ZENOHCXX_LIBRARY}
            INTERFACE_INCLUDE_DIRECTORIES ${ZENOHCXX_INCLUDE_DIR})
    else()
        set(HEADER_ONLY_BUILD ON)
        message(STATUS "zenohcxx not found, building as header-only library (JSON-RPC functionality only)")
        message(STATUS "To enable full Zenoh support, install zenohcxx library")
    endif()
endif()

# Try to find nlohmann_json
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    # Try with PkgConfig
    pkg_check_modules(nlohmann_json QUIET nlohmann_json)
    if(NOT nlohmann_json_FOUND)
        # Try to find in system paths
        find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp
            PATHS /usr/include /usr/local/include
            PATH_SUFFIXES nlohmann)
        if(NLOHMANN_JSON_INCLUDE_DIR)
            add_library(nlohmann_json INTERFACE)
            target_include_directories(nlohmann_json INTERFACE ${NLOHMANN_JSON_INCLUDE_DIR})
        else()
            message(FATAL_ERROR "nlohmann/json not found. Please install nlohmann-json-dev package.")
        endif()
    endif()
endif()

# Include directories
include_directories(include)

# Create the library
if(NOT HEADER_ONLY_BUILD)
    add_library(zenoh_rpc STATIC
        src/errors.cpp
        src/jsonrpc_proto.cpp
        src/jsonrpc_client.cpp
        src/jsonrpc_server.cpp
        src/session.cpp
    )
    
    # Link libraries
    target_link_libraries(zenoh_rpc
        zenohcxx::zenohc
        nlohmann_json::nlohmann_json
    )
    
    # Include directories
    target_include_directories(zenoh_rpc PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
else()
    # Header-only library for when zenohcxx is not available
    add_library(zenoh_rpc INTERFACE)
    target_include_directories(zenoh_rpc INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(zenoh_rpc INTERFACE
        nlohmann_json::nlohmann_json
    )
    target_compile_definitions(zenoh_rpc INTERFACE ZENOH_RPC_HEADER_ONLY)
endif()

# Create examples
if(NOT HEADER_ONLY_BUILD)
    file(GLOB EXAMPLE_SOURCES "examples/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_NAME} zenoh_rpc)
    endforeach()
else()
    message(STATUS "Skipping examples in header-only mode. Install zenohcxx to build examples.")
endif()

# Install targets
if(NOT HEADER_ONLY_BUILD)
    install(TARGETS zenoh_rpc
        EXPORT zenoh-rpc-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
else()
    install(TARGETS zenoh_rpc
        EXPORT zenoh-rpc-targets
        INCLUDES DESTINATION include
    )
endif()

# Install headers
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# Install CMake config files
install(EXPORT zenoh-rpc-targets
    FILE zenoh-rpc-targets.cmake
    NAMESPACE zenoh-rpc::
    DESTINATION lib/cmake/zenoh-rpc
)