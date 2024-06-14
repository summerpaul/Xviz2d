/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:09:04
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-14 20:33:47
 */
#include <stdint.h>

#ifndef __SCENE_POLYGON_H__
#define __SCENE_POLYGON_H__

#include "scene_object.h"

namespace scene
{
    class ScenePolygon : public SceneObject
    {

    public:
        typedef std::shared_ptr<ScenePolygon> Ptr;
        ScenePolygon() = default;
        virtual ~ScenePolygon() {}

        const Polygon::Ptr GetPolygon() const
        {
            return std::dynamic_pointer_cast<basis::Polygon>(m_object);
        }

        void SetPolygon(const basis::Polygon &polygon)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<basis::Polygon>();
            }
            *std::dynamic_pointer_cast<basis::Polygon>(m_object) = polygon;
        }

        virtual void Clear() override {}
    };

} // na

#endif /* __SCENE_POLYGON_H__ */
