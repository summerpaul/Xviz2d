/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:09:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 10:26:11
 */
#include <stdint.h>

#ifndef __SCENE_POLYGON_ARRAY_H__
#define __SCENE_POLYGON_ARRAY_H__

#include "scene_object.h"

namespace scene
{
    class ScenePolygonArray : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePolygonArray> Ptr;
        ScenePolygonArray() = default;
        virtual ~ScenePolygonArray() {}
        virtual void Clear() override {}

        const PolygonArray::Ptr GetPolygons() const
        {
            return std::dynamic_pointer_cast<PolygonArray>(m_object);
        }
        void SetPolygons(const PolygonArray &polygons)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<PolygonArray>();
            }
            *std::dynamic_pointer_cast<PolygonArray>(m_object) = polygons;
        }
    };

} // namespace scene

#endif /* __SCENE_POLYGON_ARRAY_H__ */
