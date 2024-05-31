/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:07:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 00:40:31
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
        ~ScenePath() {}

        void SetPath(const Path &path)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<Path>();
            }
            *std::dynamic_pointer_cast<Path>(m_object) = path;
        }

        const Path::Ptr GetPath() const
        {
            return std::dynamic_pointer_cast<Path>(m_object);
        }

        // virtual void Clear() override { std::dynamic_pointer_cast<Path>(std::move(m_object))->points.clear(); }
    };

} // nam
#endif /* __SCENE_PATH_H__ */
