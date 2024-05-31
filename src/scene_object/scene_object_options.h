/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 20:21:23
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 18:13:24
 */

#ifndef __SCENE_OBJECT_OPTIONS_H__
#define __SCENE_OBJECT_OPTIONS_H__
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

    struct SceneObjectOptions
    {
        SceneObjectOptions() {}
        unsigned int color = 0;
        int type = 0;
        std::string name;
        bool isShowID = false;
        bool isVisible = true;
        float thickness = 0.05f;
        float radius = 0.05f;
        float length = 1.0f;
        bool isSelected = false;
    };
} // namespace scene

#endif /* __SCENE_OBJECT_OPTIONS_H__ */
