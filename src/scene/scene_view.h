/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 17:40:53
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 17:41:09
 */
#include <stdint.h>

#ifndef __SCENE_VIEW_H__
#define __SCENE_VIEW_H__
#include "basis/data_types.h"
#include "basis/xviz_math.h"

#include <memory>

namespace scene
{
    using namespace basis;

    struct SceneView
    {
        SceneView() = default;
        typedef std::shared_ptr<SceneView> Ptr;
        float scale = 0.02f;
        float invScale = 50.0f;
        Vec2f position{0.0f, 20.0f};
        Vec2f origin{-4.0f, -4.0f};
        Vec2f size;

        Vec2f FromLocal(const Vec2f &local_pt)
        {
            Vec2f world_pt;
            world_pt.x = position.x + (local_pt.x - origin.x) * invScale;
            world_pt.y = position.y + (size.y - (local_pt.y - origin.y) * invScale);
            return world_pt;
        }

        Vec2f ToLocal(const Vec2f &world_pt)
        {
            Vec2f local_pt;
            local_pt.x = origin.x + (world_pt.x - position.x) * scale;
            local_pt.y = origin.y + (size.y - (world_pt.y - position.y)) * scale;
            return local_pt;
        }

        void DragScene(const Vec2f &mouse_pose_prev, const Vec2f &mouse_pose_now, const Vec2f &origin_prev)
        {
            float delta_x = mouse_pose_now.x - mouse_pose_prev.x;
            float delta_y = mouse_pose_now.y - mouse_pose_prev.y;
            origin.x = origin_prev.x - delta_x * scale;
            origin.y = origin_prev.y + delta_y * scale;
        }

        void SetScale(float scale)
        {
            this->scale = scale;
            this->invScale = 1.0f / scale;
        }

        void SetPosition(const Vec2f &position)
        {
            this->position = position;
        }
        void SetOrigin(const Vec2f &origin)
        {
            this->origin = origin;
        }

        void SetSize(const Vec2f &size)
        {
            this->size = size;
        }

        void OriginToCenter()
        {
            origin.x = -size.x * 0.5f * scale;
            origin.y = -size.y * 0.5f * scale;
        }

        const Vec2f &GetViewRectMin() const
        {
            return this->position;
        }
        const Vec2f GetViewRectMax()
        {
            return (this->position + this->size);
        }
    };

}
#endif /* __SCENE_VIEW_H__ */
