/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:10:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 10:10:43
 */
#include <stdint.h>

#ifndef __SCENE_TRANSFORM_NODE_H__
#define __SCENE_TRANSFORM_NODE_H__
#include "scene_object.h"

namespace scene
{
    class SceneTransformNode : public SceneObject
    {
    public:
        typedef std::shared_ptr<SceneTransformNode> Ptr;
        SceneTransformNode() = default;
        virtual ~SceneTransformNode() = default;

        const TransformNode &GetTransformNode() const { return m_tfNode; }

        void SetTransformNode(const TransformNode &tfNode) { m_tfNode = tfNode; }

    protected:
        TransformNode m_tfNode;
    };

} // name

#endif /* __SCENE_TRANSFORM_NODE_H__ */
