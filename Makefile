# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vision/users/flb/internship/zenoh-cpp-rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vision/users/flb/internship/zenoh-cpp-rpc

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vision/users/flb/internship/zenoh-cpp-rpc/CMakeFiles /home/vision/users/flb/internship/zenoh-cpp-rpc//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vision/users/flb/internship/zenoh-cpp-rpc/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named zenoh_rpc

# Build rule for target.
zenoh_rpc: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 zenoh_rpc
.PHONY : zenoh_rpc

# fast build rule for target.
zenoh_rpc/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/build
.PHONY : zenoh_rpc/fast

#=============================================================================
# Target rules for targets named client_example

# Build rule for target.
client_example: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 client_example
.PHONY : client_example

# fast build rule for target.
client_example/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/client_example.dir/build.make CMakeFiles/client_example.dir/build
.PHONY : client_example/fast

#=============================================================================
# Target rules for targets named server_example

# Build rule for target.
server_example: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 server_example
.PHONY : server_example

# fast build rule for target.
server_example/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/server_example.dir/build.make CMakeFiles/server_example.dir/build
.PHONY : server_example/fast

#=============================================================================
# Target rules for targets named session_management_example

# Build rule for target.
session_management_example: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 session_management_example
.PHONY : session_management_example

# fast build rule for target.
session_management_example/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/session_management_example.dir/build.make CMakeFiles/session_management_example.dir/build
.PHONY : session_management_example/fast

#=============================================================================
# Target rules for targets named simple_client

# Build rule for target.
simple_client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 simple_client
.PHONY : simple_client

# fast build rule for target.
simple_client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_client.dir/build.make CMakeFiles/simple_client.dir/build
.PHONY : simple_client/fast

#=============================================================================
# Target rules for targets named simple_server

# Build rule for target.
simple_server: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 simple_server
.PHONY : simple_server

# fast build rule for target.
simple_server/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_server.dir/build.make CMakeFiles/simple_server.dir/build
.PHONY : simple_server/fast

#=============================================================================
# Target rules for targets named simple_query_client

# Build rule for target.
simple_query_client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 simple_query_client
.PHONY : simple_query_client

# fast build rule for target.
simple_query_client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_client.dir/build.make CMakeFiles/simple_query_client.dir/build
.PHONY : simple_query_client/fast

#=============================================================================
# Target rules for targets named simple_query_server

# Build rule for target.
simple_query_server: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 simple_query_server
.PHONY : simple_query_server

# fast build rule for target.
simple_query_server/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_server.dir/build.make CMakeFiles/simple_query_server.dir/build
.PHONY : simple_query_server/fast

#=============================================================================
# Target rules for targets named test_client_improvements

# Build rule for target.
test_client_improvements: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_client_improvements
.PHONY : test_client_improvements

# fast build rule for target.
test_client_improvements/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_improvements.dir/build.make CMakeFiles/test_client_improvements.dir/build
.PHONY : test_client_improvements/fast

#=============================================================================
# Target rules for targets named test_client_msgpack

# Build rule for target.
test_client_msgpack: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_client_msgpack
.PHONY : test_client_msgpack

# fast build rule for target.
test_client_msgpack/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_msgpack.dir/build.make CMakeFiles/test_client_msgpack.dir/build
.PHONY : test_client_msgpack/fast

#=============================================================================
# Target rules for targets named test_error_handling

# Build rule for target.
test_error_handling: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_error_handling
.PHONY : test_error_handling

# fast build rule for target.
test_error_handling/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_error_handling.dir/build.make CMakeFiles/test_error_handling.dir/build
.PHONY : test_error_handling/fast

#=============================================================================
# Target rules for targets named test_jsonrpc

# Build rule for target.
test_jsonrpc: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_jsonrpc
.PHONY : test_jsonrpc

# fast build rule for target.
test_jsonrpc/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_jsonrpc.dir/build.make CMakeFiles/test_jsonrpc.dir/build
.PHONY : test_jsonrpc/fast

#=============================================================================
# Target rules for targets named test_msgpack_support

# Build rule for target.
test_msgpack_support: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_msgpack_support
.PHONY : test_msgpack_support

# fast build rule for target.
test_msgpack_support/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_msgpack_support.dir/build.make CMakeFiles/test_msgpack_support.dir/build
.PHONY : test_msgpack_support/fast

#=============================================================================
# Target rules for targets named test_parameter_handling

# Build rule for target.
test_parameter_handling: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_parameter_handling
.PHONY : test_parameter_handling

# fast build rule for target.
test_parameter_handling/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_parameter_handling.dir/build.make CMakeFiles/test_parameter_handling.dir/build
.PHONY : test_parameter_handling/fast

#=============================================================================
# Target rules for targets named test_query_communication

# Build rule for target.
test_query_communication: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_query_communication
.PHONY : test_query_communication

# fast build rule for target.
test_query_communication/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_query_communication.dir/build.make CMakeFiles/test_query_communication.dir/build
.PHONY : test_query_communication/fast

#=============================================================================
# Target rules for targets named test_zenoh

# Build rule for target.
test_zenoh: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_zenoh
.PHONY : test_zenoh

# fast build rule for target.
test_zenoh/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_zenoh.dir/build.make CMakeFiles/test_zenoh.dir/build
.PHONY : test_zenoh/fast

examples/client_example.o: examples/client_example.cpp.o
.PHONY : examples/client_example.o

# target to build an object file
examples/client_example.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/client_example.dir/build.make CMakeFiles/client_example.dir/examples/client_example.cpp.o
.PHONY : examples/client_example.cpp.o

examples/client_example.i: examples/client_example.cpp.i
.PHONY : examples/client_example.i

# target to preprocess a source file
examples/client_example.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/client_example.dir/build.make CMakeFiles/client_example.dir/examples/client_example.cpp.i
.PHONY : examples/client_example.cpp.i

examples/client_example.s: examples/client_example.cpp.s
.PHONY : examples/client_example.s

# target to generate assembly for a file
examples/client_example.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/client_example.dir/build.make CMakeFiles/client_example.dir/examples/client_example.cpp.s
.PHONY : examples/client_example.cpp.s

examples/server_example.o: examples/server_example.cpp.o
.PHONY : examples/server_example.o

# target to build an object file
examples/server_example.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/server_example.dir/build.make CMakeFiles/server_example.dir/examples/server_example.cpp.o
.PHONY : examples/server_example.cpp.o

examples/server_example.i: examples/server_example.cpp.i
.PHONY : examples/server_example.i

# target to preprocess a source file
examples/server_example.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/server_example.dir/build.make CMakeFiles/server_example.dir/examples/server_example.cpp.i
.PHONY : examples/server_example.cpp.i

examples/server_example.s: examples/server_example.cpp.s
.PHONY : examples/server_example.s

# target to generate assembly for a file
examples/server_example.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/server_example.dir/build.make CMakeFiles/server_example.dir/examples/server_example.cpp.s
.PHONY : examples/server_example.cpp.s

examples/session_management_example.o: examples/session_management_example.cpp.o
.PHONY : examples/session_management_example.o

# target to build an object file
examples/session_management_example.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/session_management_example.dir/build.make CMakeFiles/session_management_example.dir/examples/session_management_example.cpp.o
.PHONY : examples/session_management_example.cpp.o

examples/session_management_example.i: examples/session_management_example.cpp.i
.PHONY : examples/session_management_example.i

# target to preprocess a source file
examples/session_management_example.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/session_management_example.dir/build.make CMakeFiles/session_management_example.dir/examples/session_management_example.cpp.i
.PHONY : examples/session_management_example.cpp.i

examples/session_management_example.s: examples/session_management_example.cpp.s
.PHONY : examples/session_management_example.s

# target to generate assembly for a file
examples/session_management_example.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/session_management_example.dir/build.make CMakeFiles/session_management_example.dir/examples/session_management_example.cpp.s
.PHONY : examples/session_management_example.cpp.s

src/errors.o: src/errors.cpp.o
.PHONY : src/errors.o

# target to build an object file
src/errors.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/errors.cpp.o
.PHONY : src/errors.cpp.o

src/errors.i: src/errors.cpp.i
.PHONY : src/errors.i

# target to preprocess a source file
src/errors.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/errors.cpp.i
.PHONY : src/errors.cpp.i

src/errors.s: src/errors.cpp.s
.PHONY : src/errors.s

# target to generate assembly for a file
src/errors.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/errors.cpp.s
.PHONY : src/errors.cpp.s

src/jsonrpc_client.o: src/jsonrpc_client.cpp.o
.PHONY : src/jsonrpc_client.o

# target to build an object file
src/jsonrpc_client.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_client.cpp.o
.PHONY : src/jsonrpc_client.cpp.o

src/jsonrpc_client.i: src/jsonrpc_client.cpp.i
.PHONY : src/jsonrpc_client.i

# target to preprocess a source file
src/jsonrpc_client.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_client.cpp.i
.PHONY : src/jsonrpc_client.cpp.i

src/jsonrpc_client.s: src/jsonrpc_client.cpp.s
.PHONY : src/jsonrpc_client.s

# target to generate assembly for a file
src/jsonrpc_client.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_client.cpp.s
.PHONY : src/jsonrpc_client.cpp.s

src/jsonrpc_proto.o: src/jsonrpc_proto.cpp.o
.PHONY : src/jsonrpc_proto.o

# target to build an object file
src/jsonrpc_proto.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_proto.cpp.o
.PHONY : src/jsonrpc_proto.cpp.o

src/jsonrpc_proto.i: src/jsonrpc_proto.cpp.i
.PHONY : src/jsonrpc_proto.i

# target to preprocess a source file
src/jsonrpc_proto.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_proto.cpp.i
.PHONY : src/jsonrpc_proto.cpp.i

src/jsonrpc_proto.s: src/jsonrpc_proto.cpp.s
.PHONY : src/jsonrpc_proto.s

# target to generate assembly for a file
src/jsonrpc_proto.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_proto.cpp.s
.PHONY : src/jsonrpc_proto.cpp.s

src/jsonrpc_server.o: src/jsonrpc_server.cpp.o
.PHONY : src/jsonrpc_server.o

# target to build an object file
src/jsonrpc_server.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_server.cpp.o
.PHONY : src/jsonrpc_server.cpp.o

src/jsonrpc_server.i: src/jsonrpc_server.cpp.i
.PHONY : src/jsonrpc_server.i

# target to preprocess a source file
src/jsonrpc_server.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_server.cpp.i
.PHONY : src/jsonrpc_server.cpp.i

src/jsonrpc_server.s: src/jsonrpc_server.cpp.s
.PHONY : src/jsonrpc_server.s

# target to generate assembly for a file
src/jsonrpc_server.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/jsonrpc_server.cpp.s
.PHONY : src/jsonrpc_server.cpp.s

src/session.o: src/session.cpp.o
.PHONY : src/session.o

# target to build an object file
src/session.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/session.cpp.o
.PHONY : src/session.cpp.o

src/session.i: src/session.cpp.i
.PHONY : src/session.i

# target to preprocess a source file
src/session.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/session.cpp.i
.PHONY : src/session.cpp.i

src/session.s: src/session.cpp.s
.PHONY : src/session.s

# target to generate assembly for a file
src/session.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zenoh_rpc.dir/build.make CMakeFiles/zenoh_rpc.dir/src/session.cpp.s
.PHONY : src/session.cpp.s

tests/test_client_improvements.o: tests/test_client_improvements.cpp.o
.PHONY : tests/test_client_improvements.o

# target to build an object file
tests/test_client_improvements.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_improvements.dir/build.make CMakeFiles/test_client_improvements.dir/tests/test_client_improvements.cpp.o
.PHONY : tests/test_client_improvements.cpp.o

tests/test_client_improvements.i: tests/test_client_improvements.cpp.i
.PHONY : tests/test_client_improvements.i

# target to preprocess a source file
tests/test_client_improvements.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_improvements.dir/build.make CMakeFiles/test_client_improvements.dir/tests/test_client_improvements.cpp.i
.PHONY : tests/test_client_improvements.cpp.i

tests/test_client_improvements.s: tests/test_client_improvements.cpp.s
.PHONY : tests/test_client_improvements.s

# target to generate assembly for a file
tests/test_client_improvements.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_improvements.dir/build.make CMakeFiles/test_client_improvements.dir/tests/test_client_improvements.cpp.s
.PHONY : tests/test_client_improvements.cpp.s

tests/test_client_msgpack.o: tests/test_client_msgpack.cpp.o
.PHONY : tests/test_client_msgpack.o

# target to build an object file
tests/test_client_msgpack.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_msgpack.dir/build.make CMakeFiles/test_client_msgpack.dir/tests/test_client_msgpack.cpp.o
.PHONY : tests/test_client_msgpack.cpp.o

tests/test_client_msgpack.i: tests/test_client_msgpack.cpp.i
.PHONY : tests/test_client_msgpack.i

# target to preprocess a source file
tests/test_client_msgpack.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_msgpack.dir/build.make CMakeFiles/test_client_msgpack.dir/tests/test_client_msgpack.cpp.i
.PHONY : tests/test_client_msgpack.cpp.i

tests/test_client_msgpack.s: tests/test_client_msgpack.cpp.s
.PHONY : tests/test_client_msgpack.s

# target to generate assembly for a file
tests/test_client_msgpack.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_client_msgpack.dir/build.make CMakeFiles/test_client_msgpack.dir/tests/test_client_msgpack.cpp.s
.PHONY : tests/test_client_msgpack.cpp.s

tests/test_error_handling.o: tests/test_error_handling.cpp.o
.PHONY : tests/test_error_handling.o

# target to build an object file
tests/test_error_handling.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_error_handling.dir/build.make CMakeFiles/test_error_handling.dir/tests/test_error_handling.cpp.o
.PHONY : tests/test_error_handling.cpp.o

tests/test_error_handling.i: tests/test_error_handling.cpp.i
.PHONY : tests/test_error_handling.i

# target to preprocess a source file
tests/test_error_handling.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_error_handling.dir/build.make CMakeFiles/test_error_handling.dir/tests/test_error_handling.cpp.i
.PHONY : tests/test_error_handling.cpp.i

tests/test_error_handling.s: tests/test_error_handling.cpp.s
.PHONY : tests/test_error_handling.s

# target to generate assembly for a file
tests/test_error_handling.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_error_handling.dir/build.make CMakeFiles/test_error_handling.dir/tests/test_error_handling.cpp.s
.PHONY : tests/test_error_handling.cpp.s

tests/test_jsonrpc.o: tests/test_jsonrpc.cpp.o
.PHONY : tests/test_jsonrpc.o

# target to build an object file
tests/test_jsonrpc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_jsonrpc.dir/build.make CMakeFiles/test_jsonrpc.dir/tests/test_jsonrpc.cpp.o
.PHONY : tests/test_jsonrpc.cpp.o

tests/test_jsonrpc.i: tests/test_jsonrpc.cpp.i
.PHONY : tests/test_jsonrpc.i

# target to preprocess a source file
tests/test_jsonrpc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_jsonrpc.dir/build.make CMakeFiles/test_jsonrpc.dir/tests/test_jsonrpc.cpp.i
.PHONY : tests/test_jsonrpc.cpp.i

tests/test_jsonrpc.s: tests/test_jsonrpc.cpp.s
.PHONY : tests/test_jsonrpc.s

# target to generate assembly for a file
tests/test_jsonrpc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_jsonrpc.dir/build.make CMakeFiles/test_jsonrpc.dir/tests/test_jsonrpc.cpp.s
.PHONY : tests/test_jsonrpc.cpp.s

tests/test_msgpack_support.o: tests/test_msgpack_support.cpp.o
.PHONY : tests/test_msgpack_support.o

# target to build an object file
tests/test_msgpack_support.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_msgpack_support.dir/build.make CMakeFiles/test_msgpack_support.dir/tests/test_msgpack_support.cpp.o
.PHONY : tests/test_msgpack_support.cpp.o

tests/test_msgpack_support.i: tests/test_msgpack_support.cpp.i
.PHONY : tests/test_msgpack_support.i

# target to preprocess a source file
tests/test_msgpack_support.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_msgpack_support.dir/build.make CMakeFiles/test_msgpack_support.dir/tests/test_msgpack_support.cpp.i
.PHONY : tests/test_msgpack_support.cpp.i

tests/test_msgpack_support.s: tests/test_msgpack_support.cpp.s
.PHONY : tests/test_msgpack_support.s

# target to generate assembly for a file
tests/test_msgpack_support.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_msgpack_support.dir/build.make CMakeFiles/test_msgpack_support.dir/tests/test_msgpack_support.cpp.s
.PHONY : tests/test_msgpack_support.cpp.s

tests/test_parameter_handling.o: tests/test_parameter_handling.cpp.o
.PHONY : tests/test_parameter_handling.o

# target to build an object file
tests/test_parameter_handling.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_parameter_handling.dir/build.make CMakeFiles/test_parameter_handling.dir/tests/test_parameter_handling.cpp.o
.PHONY : tests/test_parameter_handling.cpp.o

tests/test_parameter_handling.i: tests/test_parameter_handling.cpp.i
.PHONY : tests/test_parameter_handling.i

# target to preprocess a source file
tests/test_parameter_handling.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_parameter_handling.dir/build.make CMakeFiles/test_parameter_handling.dir/tests/test_parameter_handling.cpp.i
.PHONY : tests/test_parameter_handling.cpp.i

tests/test_parameter_handling.s: tests/test_parameter_handling.cpp.s
.PHONY : tests/test_parameter_handling.s

# target to generate assembly for a file
tests/test_parameter_handling.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_parameter_handling.dir/build.make CMakeFiles/test_parameter_handling.dir/tests/test_parameter_handling.cpp.s
.PHONY : tests/test_parameter_handling.cpp.s

tests/test_query_communication.o: tests/test_query_communication.cpp.o
.PHONY : tests/test_query_communication.o

# target to build an object file
tests/test_query_communication.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_query_communication.dir/build.make CMakeFiles/test_query_communication.dir/tests/test_query_communication.cpp.o
.PHONY : tests/test_query_communication.cpp.o

tests/test_query_communication.i: tests/test_query_communication.cpp.i
.PHONY : tests/test_query_communication.i

# target to preprocess a source file
tests/test_query_communication.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_query_communication.dir/build.make CMakeFiles/test_query_communication.dir/tests/test_query_communication.cpp.i
.PHONY : tests/test_query_communication.cpp.i

tests/test_query_communication.s: tests/test_query_communication.cpp.s
.PHONY : tests/test_query_communication.s

# target to generate assembly for a file
tests/test_query_communication.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_query_communication.dir/build.make CMakeFiles/test_query_communication.dir/tests/test_query_communication.cpp.s
.PHONY : tests/test_query_communication.cpp.s

tests/test_zenoh.o: tests/test_zenoh.cpp.o
.PHONY : tests/test_zenoh.o

# target to build an object file
tests/test_zenoh.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_zenoh.dir/build.make CMakeFiles/test_zenoh.dir/tests/test_zenoh.cpp.o
.PHONY : tests/test_zenoh.cpp.o

tests/test_zenoh.i: tests/test_zenoh.cpp.i
.PHONY : tests/test_zenoh.i

# target to preprocess a source file
tests/test_zenoh.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_zenoh.dir/build.make CMakeFiles/test_zenoh.dir/tests/test_zenoh.cpp.i
.PHONY : tests/test_zenoh.cpp.i

tests/test_zenoh.s: tests/test_zenoh.cpp.s
.PHONY : tests/test_zenoh.s

# target to generate assembly for a file
tests/test_zenoh.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_zenoh.dir/build.make CMakeFiles/test_zenoh.dir/tests/test_zenoh.cpp.s
.PHONY : tests/test_zenoh.cpp.s

tools/simple_client.o: tools/simple_client.cpp.o
.PHONY : tools/simple_client.o

# target to build an object file
tools/simple_client.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_client.dir/build.make CMakeFiles/simple_client.dir/tools/simple_client.cpp.o
.PHONY : tools/simple_client.cpp.o

tools/simple_client.i: tools/simple_client.cpp.i
.PHONY : tools/simple_client.i

# target to preprocess a source file
tools/simple_client.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_client.dir/build.make CMakeFiles/simple_client.dir/tools/simple_client.cpp.i
.PHONY : tools/simple_client.cpp.i

tools/simple_client.s: tools/simple_client.cpp.s
.PHONY : tools/simple_client.s

# target to generate assembly for a file
tools/simple_client.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_client.dir/build.make CMakeFiles/simple_client.dir/tools/simple_client.cpp.s
.PHONY : tools/simple_client.cpp.s

tools/simple_query_client.o: tools/simple_query_client.cpp.o
.PHONY : tools/simple_query_client.o

# target to build an object file
tools/simple_query_client.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_client.dir/build.make CMakeFiles/simple_query_client.dir/tools/simple_query_client.cpp.o
.PHONY : tools/simple_query_client.cpp.o

tools/simple_query_client.i: tools/simple_query_client.cpp.i
.PHONY : tools/simple_query_client.i

# target to preprocess a source file
tools/simple_query_client.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_client.dir/build.make CMakeFiles/simple_query_client.dir/tools/simple_query_client.cpp.i
.PHONY : tools/simple_query_client.cpp.i

tools/simple_query_client.s: tools/simple_query_client.cpp.s
.PHONY : tools/simple_query_client.s

# target to generate assembly for a file
tools/simple_query_client.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_client.dir/build.make CMakeFiles/simple_query_client.dir/tools/simple_query_client.cpp.s
.PHONY : tools/simple_query_client.cpp.s

tools/simple_query_server.o: tools/simple_query_server.cpp.o
.PHONY : tools/simple_query_server.o

# target to build an object file
tools/simple_query_server.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_server.dir/build.make CMakeFiles/simple_query_server.dir/tools/simple_query_server.cpp.o
.PHONY : tools/simple_query_server.cpp.o

tools/simple_query_server.i: tools/simple_query_server.cpp.i
.PHONY : tools/simple_query_server.i

# target to preprocess a source file
tools/simple_query_server.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_server.dir/build.make CMakeFiles/simple_query_server.dir/tools/simple_query_server.cpp.i
.PHONY : tools/simple_query_server.cpp.i

tools/simple_query_server.s: tools/simple_query_server.cpp.s
.PHONY : tools/simple_query_server.s

# target to generate assembly for a file
tools/simple_query_server.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_query_server.dir/build.make CMakeFiles/simple_query_server.dir/tools/simple_query_server.cpp.s
.PHONY : tools/simple_query_server.cpp.s

tools/simple_server.o: tools/simple_server.cpp.o
.PHONY : tools/simple_server.o

# target to build an object file
tools/simple_server.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_server.dir/build.make CMakeFiles/simple_server.dir/tools/simple_server.cpp.o
.PHONY : tools/simple_server.cpp.o

tools/simple_server.i: tools/simple_server.cpp.i
.PHONY : tools/simple_server.i

# target to preprocess a source file
tools/simple_server.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_server.dir/build.make CMakeFiles/simple_server.dir/tools/simple_server.cpp.i
.PHONY : tools/simple_server.cpp.i

tools/simple_server.s: tools/simple_server.cpp.s
.PHONY : tools/simple_server.s

# target to generate assembly for a file
tools/simple_server.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/simple_server.dir/build.make CMakeFiles/simple_server.dir/tools/simple_server.cpp.s
.PHONY : tools/simple_server.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... client_example"
	@echo "... server_example"
	@echo "... session_management_example"
	@echo "... simple_client"
	@echo "... simple_query_client"
	@echo "... simple_query_server"
	@echo "... simple_server"
	@echo "... test_client_improvements"
	@echo "... test_client_msgpack"
	@echo "... test_error_handling"
	@echo "... test_jsonrpc"
	@echo "... test_msgpack_support"
	@echo "... test_parameter_handling"
	@echo "... test_query_communication"
	@echo "... test_zenoh"
	@echo "... zenoh_rpc"
	@echo "... examples/client_example.o"
	@echo "... examples/client_example.i"
	@echo "... examples/client_example.s"
	@echo "... examples/server_example.o"
	@echo "... examples/server_example.i"
	@echo "... examples/server_example.s"
	@echo "... examples/session_management_example.o"
	@echo "... examples/session_management_example.i"
	@echo "... examples/session_management_example.s"
	@echo "... src/errors.o"
	@echo "... src/errors.i"
	@echo "... src/errors.s"
	@echo "... src/jsonrpc_client.o"
	@echo "... src/jsonrpc_client.i"
	@echo "... src/jsonrpc_client.s"
	@echo "... src/jsonrpc_proto.o"
	@echo "... src/jsonrpc_proto.i"
	@echo "... src/jsonrpc_proto.s"
	@echo "... src/jsonrpc_server.o"
	@echo "... src/jsonrpc_server.i"
	@echo "... src/jsonrpc_server.s"
	@echo "... src/session.o"
	@echo "... src/session.i"
	@echo "... src/session.s"
	@echo "... tests/test_client_improvements.o"
	@echo "... tests/test_client_improvements.i"
	@echo "... tests/test_client_improvements.s"
	@echo "... tests/test_client_msgpack.o"
	@echo "... tests/test_client_msgpack.i"
	@echo "... tests/test_client_msgpack.s"
	@echo "... tests/test_error_handling.o"
	@echo "... tests/test_error_handling.i"
	@echo "... tests/test_error_handling.s"
	@echo "... tests/test_jsonrpc.o"
	@echo "... tests/test_jsonrpc.i"
	@echo "... tests/test_jsonrpc.s"
	@echo "... tests/test_msgpack_support.o"
	@echo "... tests/test_msgpack_support.i"
	@echo "... tests/test_msgpack_support.s"
	@echo "... tests/test_parameter_handling.o"
	@echo "... tests/test_parameter_handling.i"
	@echo "... tests/test_parameter_handling.s"
	@echo "... tests/test_query_communication.o"
	@echo "... tests/test_query_communication.i"
	@echo "... tests/test_query_communication.s"
	@echo "... tests/test_zenoh.o"
	@echo "... tests/test_zenoh.i"
	@echo "... tests/test_zenoh.s"
	@echo "... tools/simple_client.o"
	@echo "... tools/simple_client.i"
	@echo "... tools/simple_client.s"
	@echo "... tools/simple_query_client.o"
	@echo "... tools/simple_query_client.i"
	@echo "... tools/simple_query_client.s"
	@echo "... tools/simple_query_server.o"
	@echo "... tools/simple_query_server.i"
	@echo "... tools/simple_query_server.s"
	@echo "... tools/simple_server.o"
	@echo "... tools/simple_server.i"
	@echo "... tools/simple_server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

