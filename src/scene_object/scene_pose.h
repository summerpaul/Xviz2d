/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:03:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 09:08:03
 */
#include <stdint.h>

#ifndef __SCENE_POSE_H__
#define __SCENE_POSE_H__

#include "scene_object.h"

namespace scene
{
    class ScenePose : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePose> Ptr;
        ScenePose() = default;
        ~ScenePose() = default;
        const basis::Pose::Ptr GetPose() const { return std::dynamic_pointer_cast<Pose>(m_object); }

        void SetPose(const basis::Pose &pose)
        {

            if (m_object == nullptr)
            {
                m_object = std::make_shared<Pose>();
            }
            *std::dynamic_pointer_cast<Pose>(m_object) = pose;
        }
    };

} // namespace
#endif /* __SCENE_POSE_H__ */
