/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:07:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:07:57
 */
#include <stdint.h>

#ifndef __SCENE_PATH_H__
#define __SCENE_PATH_H__

#include "scene_object.h"

namespace scene
{
    class ScenePath : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePath> Ptr;
        ScenePath() = default;
        ~ScenePath() { m_path.points.clear(); }

        void SetPath(const Path &path) { m_path = path; }
        const Path &GetPath() const { return m_path; }

        virtual void Clear() override { m_path.points.clear(); }

    protected:
        Path m_path;
    };

} // nam
#endif /* __SCENE_PATH_H__ */
