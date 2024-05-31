/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:03:40
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:04:25
 */
#include "tf_tree.h"
#include <algorithm>

namespace scene
{
    void TFTree::InsertTransform(const std::string &name, const std::string &parent_name, const Transform &tf)
    {
        m_tfNodeMap[name].frameId = name;
        m_tfNodeMap[name].parentFrameId = parent_name;
        m_tfNodeMap[name].trans = tf.trans;
        m_tfNodeMap[name].yaw = tf.rot.GetAngle();
    }

    void TFTree::UpdateTransform(const std::string &name, const Transform &tf)
    {
        m_tfNodeMap[name].trans = tf.trans;
        m_tfNodeMap[name].yaw = tf.rot.GetAngle();
    }

    bool TFTree::CanTransform(const std::string &target_frame, const std::string &source_frame)
    {
        if (m_tfNodeMap.find(target_frame) == m_tfNodeMap.end() ||
            m_tfNodeMap.find(source_frame) == m_tfNodeMap.end())
        {
            return false;
        }

        return true;
    }

    Transform TFTree::LookupTransform(const std::string &target_frame, const std::string &source_frame)
    {
        if (source_frame == target_frame)
        {
            Transform identity;
            identity.SetIdentity();
            return identity;
        }

        auto source_to_root = NodeToRoot(source_frame);
        auto root_to_target = RootToNode(target_frame);
        return Mul(source_to_root, root_to_target);
    }

    std::vector<std::string> TFTree::GetRootToNodeFrameIdList(const std::string &frame_id)
    {
        std::vector<std::string> frameIdList;
        if (frame_id == m_rootFrameId)
        {
            return frameIdList;
        }
        std::string parent_frame_id = frame_id;
        while (parent_frame_id != ROOT_FRAME)
        {
            frameIdList.emplace_back(parent_frame_id);
            parent_frame_id = m_tfNodeMap[parent_frame_id].parentFrameId;
        }
        reverse(frameIdList.begin(), frameIdList.end());
        return frameIdList;
    }

    Transform TFTree::RootToNode(const std::string &name)
    {
        // root_to_node
        std::vector<std::string> frameIdList = GetRootToNodeFrameIdList(name);
        if (frameIdList.empty())
        {
            return {};
        }
        Transform last_tf;

        for (auto &frameId : frameIdList)
        {

            if (frameId == m_rootFrameId)
            {
                const auto &tf_node = m_tfNodeMap[frameId];
                last_tf.Set(tf_node.trans, tf_node.yaw);
                continue;
            }
            const auto &tf_node = m_tfNodeMap[frameId];
            Transform cur_tf(tf_node.trans, tf_node.yaw);
            last_tf = Mul(last_tf, cur_tf);
        }
        return last_tf;
    }

    Transform TFTree::NodeToRoot(const std::string &name)
    {
        return RootToNode(name).Inv();
    }

    const std::string &TFTree::GetRootFrameId() const
    {
        return m_rootFrameId;
    }
}
