/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 14:00:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 20:40:30
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

    basis::PoseArray ProtoToPoseArray(const xviz_msgs::Pose2fArray& proto_pose_array);

    basis::PoseArray ProtoBufToPoseArray(const std::string &buf);

    basis::Path ProtoToPath(const xviz_msgs::Path2f &proto_path);

    basis::Path ProtoBufToPath(const std::string &buff);

    basis::PathArray ProtoToPathArray(const xviz_msgs::Path2fArray &proto_paths);

    basis::PathArray ProtoBufToPathArray(const std::string &buf);

    basis::Polygon ProtoToPolygon(const xviz_msgs::Polygon2f& proto_polygon);
    
    basis::Polygon ProtoBufToPolygon(const std::string &buf);

    basis::PolygonArray ProtoToPolygonArray(const xviz_msgs::Polygon2fArray &proto_polygons);

    basis::PolygonArray ProtoBufToPolygonArray(const std::string &buf);

    basis::Circle ProtoToCircle(const xviz_msgs::Circle2f & proto_circle);

    basis::Circle ProtoBufToCircle(const std::string &buf);

    basis::CircleArray ProtoToCircleArray(const xviz_msgs::Circle2fArray &proto_circles);

    basis::CircleArray ProtoBufToCircleArray(const std::string &buf);

    basis::PointCloud ProtoToPointCloud(const xviz_msgs::PointCloud2f &proto_points);

    basis::PointCloud ProtoBufToPointCloud(const std::string &buf);

    basis::TransformNode ProtoToTransformNode(const xviz_msgs::Transform2fNode &transform);

    basis::TransformNode ProtoBufToTransformNode(const std::string &buf);

} // namespace xviz_msgs

#endif /* __MSG_CONVERT_H__ */
