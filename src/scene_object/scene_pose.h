/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:03:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:41:28
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
        const basis::Pose &GetPose() const { return m_pose; }

        void SetPose(const basis::Pose &pose) { m_pose = pose; }

    protected:
        basis::Pose m_pose;
    };

} // namespace
#endif /* __SCENE_POSE_H__ */
