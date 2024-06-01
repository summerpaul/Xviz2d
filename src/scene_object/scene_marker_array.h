/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:07:23
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 20:23:09
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
        virtual ~SceneMarkerArray() {}
        virtual void Clear() override {}

        const MarkerArray::Ptr GetMarkers() const
        {
            return std::dynamic_pointer_cast<MarkerArray>(m_object);
        }

        void SetMarkers(const MarkerArray &markers)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<MarkerArray>();
            }
            *std::dynamic_pointer_cast<MarkerArray>(m_object) = markers;
        }
    };

} // namespace  scene

#endif /* __SCENE_MARKER_ARRAY_H__ */
