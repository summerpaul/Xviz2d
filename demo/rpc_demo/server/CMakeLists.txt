cmake_minimum_required(VERSION 3.0.0)
project(server)

add_executable(server main.cc)
target_link_libraries(server  rpclib::rpc)

