/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:09:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:09:36
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
        virtual ~ScenePolygonArray() { m_polygons.polygons.clear(); }
        virtual void Clear() override { m_polygons.polygons.clear(); }

        const PolygonArray &GetPolygons() const { return m_polygons; }
        void SetPolygons(const PolygonArray &polygons) { m_polygons = polygons; }

    protected:
        PolygonArray m_polygons;
    };

} // namespace scene

#endif /* __SCENE_POLYGON_ARRAY_H__ */
