/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 14:34:13
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 14:35:16
 */
#include <stdint.h>

#ifndef __SCENE_DATA_TYPES_H__
#define __SCENE_DATA_TYPES_H__
#include "scene_object/scene_objects.h"
#include "basis/thread_safe_map.h"
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
} // namespace scene

#endif /* __SCENE_DATA_TYPES_H__ */
