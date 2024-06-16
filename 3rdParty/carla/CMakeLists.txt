project(carla_client)

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

