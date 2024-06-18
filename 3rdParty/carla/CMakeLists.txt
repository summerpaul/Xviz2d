project(carla_client)
configure_file(${PROJECT_SOURCE_DIR}/Version.h.in ${PROJECT_SOURCE_DIR}/Version.h)
set(CARLA_CLIENT_ALL_DIRS
    "client"
    "client/detail"
)

foreach(dir ${CARLA_CLIENT_ALL_DIRS})
    file(GLOB_RECURSE header_files "${dir}/*.h" "${dir}/*.hpp" "${dir}/*.hxx")
    list(APPEND ALL_HEADERS ${header_files})
    file(GLOB_RECURSE src_files "${dir}/*.cpp" )
    list(APPEND ALL_SRCS ${src_files})
endforeach()




add_library(carla_client  ${ALL_SRCS} ${ALL_HEADERS})

target_include_directories(carla_client SYSTEM PRIVATE
"${RPCLIB_INCLUDE_PATH}"
"${RECAST_INCLUDE_PATH}"
"${LIBPNG_INCLUDE_PATH}")
target_link_libraries(carla_client "${RECAST_LIB_PATH}/Recast.lib")
target_link_libraries(carla_client "${RECAST_LIB_PATH}/Detour.lib")
target_link_libraries(carla_client "${RECAST_LIB_PATH}/DetourCrowd.lib")