/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:08:32
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 10:34:35
 */
#include <stdint.h>

#ifndef __SCENE_POINT_CLOUD_H__
#define __SCENE_POINT_CLOUD_H__

#include "scene_object.h"

namespace scene
{
    class ScenePointCloud : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePointCloud> Ptr;
        ScenePointCloud() = default;
        virtual ~ScenePointCloud() {}
        virtual void Clear() override {}

        const PointCloud::Ptr GetPointCloud() const
        {
            return std::dynamic_pointer_cast<PointCloud>(m_object);
        }

        void SetPointCloud(const PointCloud &pointCloud)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<PointCloud>();
            }
            *std::dynamic_pointer_cast<PointCloud>(m_object) = pointCloud;
        }
    };

} // namespace scene

#endif /* __SCENE_POINT_CLOUD_H__ */
