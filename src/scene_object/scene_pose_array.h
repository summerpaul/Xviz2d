/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:04:58
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 10:28:44
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
        ~ScenePoseArray() {}

        virtual void Clear() override
        {
        }

        const PoseArray::Ptr GetPoses() const
        {
            return std::dynamic_pointer_cast<PoseArray>(m_object);
        }

        void SetPoses(const PoseArray &poses)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<PoseArray>();
            }
            *std::dynamic_pointer_cast<PoseArray>(m_object) = poses;
        }
    };
} // namespace

#endif /* __SCENE_POSE_ARRAY_H__ */
