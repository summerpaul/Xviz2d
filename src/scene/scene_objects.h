/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:10:17
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-31 14:48:21
 */
#include <stdint.h>

#ifndef __SCENE_OBJECTS_H__
#define __SCENE_OBJECTS_H__
#include "basis/thread_safe_map.h"

#include "scene_object/scene_pose.h"
#include "scene_object/scene_pose_array.h"
#include "scene_object/scene_path.h"
#include "scene_object/scene_path_array.h"
#include "scene_object/scene_circle.h"
#include "scene_object/scene_circle_array.h"
#include "scene_object/scene_polygon.h"
#include "scene_object/scene_polygon_array.h"
#include "scene_object/scene_marker.h"
#include "scene_object/scene_marker_array.h"
#include "scene_object/scene_point_cloud.h"
#include "scene_object/scene_transform_node.h"

#include "rolling_buffer.h"

namespace scene
{
    typedef basis::ThreadSafeMap<std::string, SceneObject::Ptr> SceneObjectMap;

    typedef basis::ThreadSafeMap<std::string, ScenePose::Ptr> ScenePoseMap;

    typedef basis::ThreadSafeMap<std::string, ScenePath::Ptr> ScenePathMap;

    typedef basis::ThreadSafeMap<std::string, SceneCircle::Ptr> SceneCircleMap;

    typedef basis::ThreadSafeMap<std::string, ScenePolygon::Ptr> ScenePolygonMap;

    typedef basis::ThreadSafeMap<std::string, SceneMarker::Ptr> SceneMarkerMap;

    typedef basis::ThreadSafeMap<std::string, ScenePointCloud::Ptr> ScenePointCloudMap;

    typedef basis::ThreadSafeMap<std::string, SceneTransformNode::Ptr> SceneTransformNodeMap;

    typedef basis::ThreadSafeMap<std::string, ScenePoseArray::Ptr> ScenePoseArrayMap;

    typedef basis::ThreadSafeMap<std::string, ScenePathArray::Ptr> ScenePathArrayMap;

    typedef basis::ThreadSafeMap<std::string, SceneCircleArray::Ptr> SceneCircleArrayMap;

    typedef basis::ThreadSafeMap<std::string, ScenePolygonArray::Ptr> ScenePolygonArrayMap;

    typedef basis::ThreadSafeMap<std::string, SceneMarkerArray::Ptr> SceneMarkerArrayMap;

    typedef std::map<int, basis::ThreadSafeMap<std::string, SceneObject::Ptr>> SceneAllObjectsMap;

    typedef std::map<std::string, std::string> SceneStringMap;

    typedef basis::ThreadSafeMap<std::string, RollingBuffer> SceneRollingBufferMap;

}
#endif /* __SCENE_OBJECTS_H__ */
