/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:08:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:08:20
 */
#include <stdint.h>

#ifndef __SCENE_PATH_ARRAY_H__
#define __SCENE_PATH_ARRAY_H__

#include "scene_object.h"

namespace scene
{
    class ScenePathArray : public SceneObject
    {
    public:
        typedef std::shared_ptr<ScenePathArray> Ptr;
        ScenePathArray() = default;
        ~ScenePathArray() { m_paths.paths.clear(); }

        virtual void Clear() override { m_paths.paths.clear(); }

        const PathArray &GetPaths() const { return m_paths; }
        void SetPaths(const PathArray &paths) { m_paths = paths; }

    protected:
        PathArray m_paths;
    };

}
#endif /* __SCENE_PATH_ARRAY_H__ */
