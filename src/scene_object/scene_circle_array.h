/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:06:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:06:32
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
        
        ~SceneCircleArray() { m_circles.circles.clear(); };

        const CircleArray &GetCircles() const { return m_circles; };

        void SetCircles(const CircleArray &circles) { m_circles = circles; };

        virtual void Clear() override { m_circles.circles.clear(); }

    protected:
        CircleArray m_circles;
    };

} // namespace scene

#endif /* __SCENE_CIRCLE_ARRAY_H__ */
