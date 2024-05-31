/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:04:58
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:28:12
 */
#include <stdint.h>

#ifndef __SCENE_POSE_ARRAY_H__
#define __SCENE_POSE_ARRAY_H__

#include "scene_object.h"
namespace scene
{
    using namespace basis;

    class ScenePoseArray : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePoseArray> Ptr;
        ScenePoseArray() = default;
        ~ScenePoseArray() { m_poses.poses.clear(); }

        virtual void Clear() override
        {
            m_poses.poses.clear();
        }

        const PoseArray &GetPoses() const { return m_poses; }

        void SetPoses(const PoseArray &poses) { m_poses = poses; }

    protected:
        PoseArray m_poses;
    };
} // namespace

#endif /* __SCENE_POSE_ARRAY_H__ */
