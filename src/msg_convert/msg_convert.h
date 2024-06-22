/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 14:00:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 15:04:35
 */
#include <stdint.h>

#ifndef __MSG_CONVERT_H__
#define __MSG_CONVERT_H__

#include "basis/data_types.h"
#include "xviz_msgs/pb/xviz_msgs.pb.h"

namespace xviz_msgs
{
    template <typename ProtoMsg>
    ProtoMsg ParseProtoMsg(const std::string &buff);

    template <typename ProtoMsg>
    std::string SerializeProtoMsg(const ProtoMsg &proto_msg);

    basis::Pose ProtoMsgToPose(const xviz_msgs::Pose2f &proto_pose);

    basis::Pose ProtoBufToPose(const std::string &buf);

    basis::PoseArray ProtoToPoseArray(const std::string &buf);

} // namespace xviz_msgs

#endif /* __MSG_CONVERT_H__ */
