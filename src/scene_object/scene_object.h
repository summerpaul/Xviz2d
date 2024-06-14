/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 20:20:22
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-14 19:41:35
 */
#include <stdint.h>

#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__
#include "basis/data_types.h"
#include "scene_object_options.h"
#include <memory>

using namespace basis;

namespace scene
{

    class SceneObject
    {
    public:
        typedef std::shared_ptr<SceneObject> Ptr;

        virtual void Clear() {}

        SceneObjectOptions &GetOptions() { return m_options; }

        void SetOptions(const SceneObjectOptions &options) { m_options = options; }

        void SetName(const std::string &name)
        {
            m_object->header.name = name;
        }

        const std::string &GetInfo() const { return m_object->header.info; }

        const std::string &GetName() const { return m_object->header.name; }

        const std::string &GetFrameId() const { return m_object->header.frameId; }

        const std::string &GetOptionsName() const { return m_options.name; }

        bool HasObject() const { return m_object != nullptr; }

    protected:
        SceneObjectOptions m_options;
        BaseObject::Ptr m_object;
    };
}

#endif /* __SCENE_OBJECT_H__ */
