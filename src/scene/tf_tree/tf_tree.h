/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:03:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:04:07
 */
#include <stdint.h>

#ifndef __TF_TREE_H__
#define __TF_TREE_H__

#include "basis/xviz_math.h"
#include "basis/data_types.h"
#include "basis/transform.h"
#include <memory>
#include <unordered_map>

namespace scene
{

    using namespace basis;

    class TFTree
    {
    public:
        typedef std::shared_ptr<TFTree> Ptr;

        void InsertTransform(const std::string &name, const std::string &parent_name, const Transform &tf);

        void UpdateTransform(const std::string &name, const Transform &tf);

        bool CanTransform(const std::string &target_frame, const std::string &source_frame);

        Transform LookupTransform(const std::string &target_frame, const std::string &source_frame);

        std::vector<std::string> GetRootToNodeFrameIdList(const std::string &frame_id);

        Transform RootToNode(const std::string &name);

        Transform NodeToRoot(const std::string &name);

        const std::string &GetRootFrameId() const;

    private:
        std::unordered_map<std::string, TransformNode> m_tfNodeMap;
        std::string m_rootFrameId = ROOT_FRAME;
    };
}

#endif /* __TF_TREE_H__ */
