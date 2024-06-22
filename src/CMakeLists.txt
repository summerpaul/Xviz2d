


add_subdirectory(xviz_msgs)

set(XVIZ_ALL_DIRS
    "app"
    "basis"
    "communication"
    "scene"
    "scene_object"
    "ui"
    "window"
    "video"
    "xviz_server"
    "msg_convert"
)

foreach(dir ${XVIZ_ALL_DIRS})
    file(GLOB_RECURSE header_files "${dir}/*.h" "${dir}/*.hpp" "${dir}/*.hxx")
    list(APPEND ALL_HEADERS ${header_files})
    file(GLOB_RECURSE src_files "${dir}/*.cpp" )
    list(APPEND ALL_SRCS ${src_files})
endforeach()

add_library(XvizLib  ${ALL_SRCS} ${ALL_HEADERS})
target_link_libraries(XvizLib    
    glad::glad  
    implot::implot 
    imgui::imgui
    cppzmq-static
    xviz_msgs
    ${FFMPEG_LIBRARIES})