/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:06:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 20:22:14
 */
#include <stdint.h>

#ifndef __SCENE_MARKER_H__
#define __SCENE_MARKER_H__

#include "scene_object.h"
namespace scene
{

    class SceneMarker : public SceneObject
    {
    public:
        typedef std::shared_ptr<SceneMarker> Ptr;

        SceneMarker() = default;

        virtual ~SceneMarker() {}

        const Marker::Ptr GetMarker() const
        {
            return std::dynamic_pointer_cast<Marker>(m_object);
        }

        void SetMarker(const Marker &marker)
        {

            if (m_object == nullptr)
            {
                m_object = std::make_shared<Marker>();
            }
            *std::dynamic_pointer_cast<Marker>(m_object) = marker;
        }
    };

}

#endif /* __SCENE_MARKER_H__ */
