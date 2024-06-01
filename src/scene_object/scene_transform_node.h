/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:10:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 20:31:13
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

        const TransformNode::Ptr GetTransformNode() const
        {
            return std::dynamic_pointer_cast<TransformNode>(m_object);
        }

        void SetTransformNode(const TransformNode &tfNode)
        {

            if (m_object == nullptr)
            {
                m_object = std::make_shared<TransformNode>();
            }
            *std::dynamic_pointer_cast<TransformNode>(m_object) = tfNode;
        }
    };

} // name

#endif /* __SCENE_TRANSFORM_NODE_H__ */
