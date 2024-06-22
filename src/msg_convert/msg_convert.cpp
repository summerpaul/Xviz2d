/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 15:01:23
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 15:04:25
 */

#include "msg_convert.h"

namespace xviz_msgs
{

    template <typename ProtoMsg>
    ProtoMsg ParseProtoMsg(const std::string &buff)
    {
        ProtoMsg proto_msg;
        proto_msg.ParseFromString(buff);
        return proto_msg;
    }

    template <typename ProtoMsg>
    std::string SerializeProtoMsg(const ProtoMsg &proto_msg)
    {
        std::string buff;
        proto_msg.SerializeToString(&buff);
        return buff;
    }

    basis::Pose ProtoMsgToPose(const xviz_msgs::Pose2f &proto_pose)
    {
        basis::Pose pose;
        pose.header.name = proto_pose.header().name();
        pose.header.frameId = proto_pose.header().frameid();
        pose.header.info = proto_pose.header().info();
        pose.pos.x = proto_pose.position().x();
        pose.pos.y = proto_pose.position().y();
        pose.yaw = proto_pose.yaw();
        pose.isValid = true;
        return pose;
    }

    basis::Pose ProtoBufToPose(const std::string &buf)
    {
        return ProtoMsgToPose(ParseProtoMsg<xviz_msgs::Pose2f>(buf));
    }

    basis::PoseArray ProtoToPoseArray(const std::string &buf)
    {
        auto proto_pose_array = ParseProtoMsg<xviz_msgs::Pose2fArray>(buf);
        basis::PoseArray pose_array;
        pose_array.header.name = proto_pose_array.header().name();
        pose_array.header.frameId = proto_pose_array.header().frameid();
        pose_array.header.info = proto_pose_array.header().info();
        for (const auto &proto_pose : proto_pose_array.posearray())
        {
            pose_array.poses.emplace_back(ProtoMsgToPose(proto_pose));
        }
        return pose_array;
    }
}