/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 20:20:22
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:44:50
 */
#include <stdint.h>

#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__
#include "basis/data_types.h"
#include "scene_object_options.h"
#include <memory>

namespace scene
{
    class SceneObject
    {
    public:
        typedef std::shared_ptr<SceneObject> Ptr;

        virtual void Clear() {}

        SceneObjectOptions &GetOptions() { return m_options; }

        void SetOptions(const SceneObjectOptions &options) { m_options = options; }

    protected:
        SceneObjectOptions m_options;
    };
}

#endif /* __SCENE_OBJECT_H__ */
