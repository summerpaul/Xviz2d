/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:05:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 10:39:25
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

        const Circle::Ptr GetCircle() const
        {
            return std::dynamic_pointer_cast<Circle>(m_object);
        }

        void SetCircle(const Circle &circle)

        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<Circle>();
            }
            *std::dynamic_pointer_cast<Circle>(m_object) = circle;
        }
    };
}
#endif /* __SCENE_CIRCLE_H__ */
