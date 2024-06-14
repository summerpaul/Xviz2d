/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:06:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-14 20:33:11
 */
#include <stdint.h>

#ifndef __SCENE_CIRCLE_ARRAY_H__
#define __SCENE_CIRCLE_ARRAY_H__

#include "scene_object.h"

namespace scene
{
    class SceneCircleArray : public SceneObject
    {

    public:
        typedef std::shared_ptr<SceneCircleArray> Ptr;

        SceneCircleArray() = default;

       virtual ~SceneCircleArray(){};

        const CircleArray::Ptr GetCircles() const
        {
            return std::dynamic_pointer_cast<CircleArray>(m_object);
        };

        void SetCircles(const CircleArray &circles)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<CircleArray>();
            }
            *std::dynamic_pointer_cast<CircleArray>(m_object) = circles;
        };

        // virtual void Clear() override { m_circles.circles.clear(); }
    };

} // namespace scene

#endif /* __SCENE_CIRCLE_ARRAY_H__ */
