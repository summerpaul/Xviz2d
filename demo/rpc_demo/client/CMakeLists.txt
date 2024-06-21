cmake_minimum_required(VERSION 3.5.0)
project(client)

# Normally, you would want to distribute Findrpclib.cmake
# within your project directory; I wanted to avoid copies
# of this file here, so I'm just setting the CMake module path.
# In your project, you don't need the following line:

find_package(rpclib REQUIRED)
add_executable(client main.cc)
target_link_libraries(client rpclib::rpc)

