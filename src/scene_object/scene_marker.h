/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:06:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:07:14
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
        
        const Marker &GetMarker() const { return m_marker; }
        
        void SetMarker(const Marker &marker) { m_marker = marker; }

    protected:
        Marker m_marker;
    };

}

#endif /* __SCENE_MARKER_H__ */
