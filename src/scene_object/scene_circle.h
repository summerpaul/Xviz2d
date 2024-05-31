/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:05:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:06:01
 */
#include <stdint.h>

#ifndef __SCENE_CIRCLE_H__
#define __SCENE_CIRCLE_H__

#include "scene_object.h"

namespace scene
{
    class SceneCircle : public SceneObject
    {
    public:
        typedef std::shared_ptr<SceneCircle> Ptr;
        SceneCircle() = default;
        virtual ~SceneCircle() = default;

        const Circle &GetCircle() const { return m_circle; }

        void SetCircle(const Circle &circle) { m_circle = circle; }

    protected:
        Circle m_circle;
    };
}
#endif /* __SCENE_CIRCLE_H__ */
