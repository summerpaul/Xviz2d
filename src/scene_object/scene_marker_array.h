/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:07:23
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:07:33
 */
#include <stdint.h>

#ifndef __SCENE_MARKER_ARRAY_H__
#define __SCENE_MARKER_ARRAY_H__

#include "scene_object.h"
namespace scene
{
    class SceneMarkerArray : public SceneObject
    {
    public:
        typedef std::shared_ptr<SceneMarkerArray> Ptr;
        SceneMarkerArray() {}
        virtual ~SceneMarkerArray() { m_markers.markers.clear(); }
        virtual void Clear() override { m_markers.markers.clear(); }

        const MarkerArray &GetMarkers() const { return m_markers; }

        void SetMarkers(const MarkerArray &markers) { m_markers = markers; }

    protected:
        MarkerArray m_markers;
    };

} // namespace  scene

#endif /* __SCENE_MARKER_ARRAY_H__ */
