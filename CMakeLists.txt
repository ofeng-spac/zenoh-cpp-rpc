cmake_minimum_required(VERSION 3.16)
project(zenoh_rpc VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# For now, build as header-only library without zenoh dependency
set(HEADER_ONLY_BUILD ON)
message(STATUS "Building zenoh-cpp-rpc as header-only library (JSON-RPC functionality only)")

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
        src/zenoh_rpc.cpp
        src/errors.cpp
        src/jsonrpc_proto.cpp
    )
    
    # Link libraries
    target_link_libraries(zenoh_rpc
        zenohcxx::lib
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