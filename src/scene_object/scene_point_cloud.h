/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:08:32
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:08:46
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
        virtual ~ScenePointCloud() { m_pointCloud.points.clear(); }
        virtual void Clear() override { m_pointCloud.points.clear(); }

        const PointCloud &GetPointCloud() const { return m_pointCloud; }

        void SetPointCloud(const PointCloud &pointCloud) { m_pointCloud = pointCloud; }

    protected:
        PointCloud m_pointCloud;
    };

} // namespace scene

#endif /* __SCENE_POINT_CLOUD_H__ */
