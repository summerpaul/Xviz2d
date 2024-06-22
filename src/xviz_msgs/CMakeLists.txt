project(xviz_msgs)

find_package(protobuf CONFIG REQUIRED)

set(PROTO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(PB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pb)

file(GLOB PROTO_FILES ${PROTO_PATH}/*.proto )

if(UNIX)
    set(PROTOC  ${CMAKE_BINARY_DIR}/vcpkg_installed/arm64-osx/tools/protobuf/protoc)
elseif(WIN32)
    set(PROTOC  ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/tools/protobuf/protoc.exe)
endif()

# 删除之前的文件
execute_process(COMMAND rm -rf ${PB_DIR})
# 创建文件夹
execute_process( COMMAND mkdir ${PB_DIR})
# 生成proto cpp文件
execute_process(COMMAND ${PROTOC} --proto_path=${PROTO_PATH} --cpp_out=${PB_DIR} ${PROTO_FILES})
execute_process(COMMAND ${PROTOC} --proto_path=${PROTO_PATH} --python_out=${PB_DIR} ${PROTO_FILES})
# 生成的源文件
file(GLOB PROTO_SRCS  ${PB_DIR}/*.cc)
# 生成的头文件
file(GLOB PROTO_HDRS ${PB_DIR}/*.h)
# 生成静态库
add_library(${PROJECT_NAME} STATIC ${PROTO_SRCS} ${PROTO_HDRS} )
target_link_libraries(${PROJECT_NAME} protobuf::libprotobuf)
