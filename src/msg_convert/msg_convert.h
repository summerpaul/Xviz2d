/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 14:00:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-24 19:33:08
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

    xviz_msgs::Vector2f Vec2fToProto(const basis::Vec2f& pt);

    basis::Pose ProtoMsgToPose(const xviz_msgs::Pose2f &proto_pose);

    basis::Pose ProtoBufToPose(const std::string &buf);

    basis::PoseArray ProtoToPoseArray(const xviz_msgs::Pose2fArray &proto_pose_array);

    basis::PoseArray ProtoBufToPoseArray(const std::string &buf);

    basis::Path ProtoToPath(const xviz_msgs::Path2f &proto_path);

    basis::Path ProtoBufToPath(const std::string &buff);

    basis::PathArray ProtoToPathArray(const xviz_msgs::Path2fArray &proto_paths);

    basis::PathArray ProtoBufToPathArray(const std::string &buf);

    basis::Polygon ProtoToPolygon(const xviz_msgs::Polygon2f &proto_polygon);

    basis::Polygon ProtoBufToPolygon(const std::string &buf);

    basis::PolygonArray ProtoToPolygonArray(const xviz_msgs::Polygon2fArray &proto_polygons);

    basis::PolygonArray ProtoBufToPolygonArray(const std::string &buf);

    basis::Circle ProtoToCircle(const xviz_msgs::Circle2f &proto_circle);

    basis::Circle ProtoBufToCircle(const std::string &buf);

    basis::CircleArray ProtoToCircleArray(const xviz_msgs::Circle2fArray &proto_circles);

    basis::CircleArray ProtoBufToCircleArray(const std::string &buf);

    basis::PointCloud ProtoToPointCloud(const xviz_msgs::PointCloud2f &proto_points);

    basis::PointCloud ProtoBufToPointCloud(const std::string &buf);

    basis::TransformNode ProtoToTransformNode(const xviz_msgs::Transform2fNode &transform);

    basis::TransformNode ProtoBufToTransformNode(const std::string &buf);

    xviz_msgs::Pose2f PoseToProto(const basis::Pose &pose);

    std::string PoseToProtoBuf(const basis::Pose &pose);

    xviz_msgs::Pose2fArray PoseArrayToProto(const basis::PoseArray &pose_array);

    std::string PoseArrayToProtoBuf(const basis::PoseArray &pose_array);

    xviz_msgs::Path2f PathToProto(const basis::Path &path);

    std::string PathToProtoBuf(const basis::Path &path);

    xviz_msgs::Path2fArray PathArrayToProto(const basis::PathArray &path_array);

    std::string PathArrayToProtoBuf(const basis::PathArray &path_array);

    xviz_msgs::Polygon2f PolygonToProto(const basis::Polygon &polygon);

    std::string PolygonToProtoBuf(const basis::Polygon &polygon);
    
    xviz_msgs::Polygon2fArray PolygonArrayToProto(const basis::PolygonArray &polygon_array);

    std::string PolygonArrayToProtoBuf(const basis::PolygonArray &polygon_array);

    xviz_msgs::Circle2f CircleToProto(const basis::Circle &circle);

    std::string CircleToProtoBuf(const basis::Circle &circle);

    xviz_msgs::Circle2fArray CircleArrayToProto(const basis::CircleArray &circle_array);

    std::string CircleArrayToProtoBuf(const basis::CircleArray &circle_array);

    xviz_msgs::PointCloud2f PointCloudToProto(const basis::PointCloud &point_cloud);

    std::string PointCloudToProtoBuf(const basis::PointCloud &point_cloud);

    xviz_msgs::Transform2fNode TransformNodeToProto(const basis::TransformNode &transform);
    

} // namespace xviz_msgs

#endif /* __MSG_CONVERT_H__ */
