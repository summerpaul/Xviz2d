project(xviz_client)

add_library(xviz_client 
        xviz_client.h
        xviz_client.cpp
        ../msg_convert/msg_convert.cpp)
target_link_libraries(xviz_client    
        cppzmq-static
        xviz_msgs)