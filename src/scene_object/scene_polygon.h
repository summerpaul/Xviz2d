/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:09:04
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:09:17
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
        ~ScenePolygon() { m_polygon.points.clear(); }

        const Polygon &GetPolygon() const { return m_polygon; }

        void SetPolygon(const Polygon &polygon) { m_polygon = polygon; }

        virtual void Clear() override { m_polygon.points.clear(); }

    protected:
        Polygon m_polygon;
    };

} // na

#endif /* __SCENE_POLYGON_H__ */
