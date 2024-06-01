/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-01 21:28:21
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 21:52:39
 */
#include <stdint.h>

#ifndef __SCENE_OBJECT_TYPE_H__
#define __SCENE_OBJECT_TYPE_H__
#include <string>
namespace scene
{
    enum SceneObjectType
    {
        PATH = 0,
        PATH_ARRAY,
        POSE,
        POSE_ARRAY,
        POINT_CLOUD,
        POLYGON,
        POLYGON_ARRAY,
        CIRCLE,
        CIRCLE_ARRAY,
        MARKER,
        MARKER_ARRAY,
        TRANSFORM_NODE,
        OBJECT_NUM
    };

    const std::string SceneObjectStr[12] = {
        "PATH",
        "PATH_ARRAY",
        "POSE",
        "POSE_ARRAY",
        "POINT_CLOUD",
        "POLYGON",
        "POLYGON_ARRAY",
        "CIRCLE",
        "CIRCLE_ARRAY",
        "MARKER",
        "MARKER_ARRAY",
        "TRANSFORM_NODE"};

} // namespace scene

#endif /* __SCENE_OBJECT_TYPE_H__ */
