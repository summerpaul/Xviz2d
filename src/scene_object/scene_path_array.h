/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:08:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-14 20:33:36
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
        virtual ~ScenePathArray() {}

        virtual void Clear() override {}

        const PathArray::Ptr GetPaths() const
        {

            return std::dynamic_pointer_cast<PathArray>(m_object);
        }
        void SetPaths(const PathArray &paths)
        {
            if (m_object == nullptr)
            {
                m_object = std::make_shared<PathArray>();
            }
            *std::dynamic_pointer_cast<PathArray>(m_object) = paths;
        }
    };

}
#endif /* __SCENE_PATH_ARRAY_H__ */
