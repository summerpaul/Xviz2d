set(XVIZ_SRCS 
    scene/scene_manager.cpp 
    scene/scene_draw.cpp
    scene/tf_tree/tf_tree.cpp
    ui/main_layer.cpp
    ui/scene_layer.cpp
    ui/plot_layer.cpp
    ui/scene_edit_layer.cpp
    window/window.cpp
    app/app.cpp
    video/texture.cpp
    video/video_capture.cpp
    )

add_library(XvizLib  ${XVIZ_SRCS})
target_link_libraries(XvizLib    
    glad::glad  
    implot::implot 
    imgui::imgui
    ${FFMPEG_LIBRARIES})