/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-22 15:01:23
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 20:26:52
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

    basis::PoseArray ProtoToPoseArray(const xviz_msgs::Pose2fArray &proto_pose_array)
    {
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

    basis::PoseArray ProtoBufToPoseArray(const std::string &buf)
    {
        return ProtoToPoseArray(ParseProtoMsg<xviz_msgs::Pose2fArray>(buf));
    }

    basis::Path ProtoToPath(const xviz_msgs::Path2f &proto_path)
    {
        basis::Path path;
        path.header.name = proto_path.header().name();
        path.header.frameId = proto_path.header().frameid();
        path.header.info = proto_path.header().info();
        for (const auto &proto_pt : proto_path.points())
        {
            path.points.emplace_back(basis::Vec2f(proto_pt.x(), proto_pt.y()));
        }
        return path;
    }

    basis::Path ProtoBufToPath(const std::string &buff)
    {
        return ProtoToPath(ParseProtoMsg<xviz_msgs::Path2f>(buff));
    }

    basis::PathArray ProtoToPathArray(const xviz_msgs::Path2fArray &proto_paths)
    {
        basis::PathArray path_array;
        path_array.header.name = proto_paths.header().name();
        path_array.header.frameId = proto_paths.header().frameid();
        path_array.header.info = proto_paths.header().info();
        for (const auto &path : proto_paths.patharray())
        {
            path_array.paths.emplace_back(ProtoToPath(path));
        }
        return path_array;
    }

    basis::PathArray ProtoBufToPathArray(const std::string &buf)
    {
        return ProtoToPathArray(ParseProtoMsg<xviz_msgs::Path2fArray>(buf));
    }

    basis::Polygon ProtoToPolygon(const xviz_msgs::Polygon2f &proto_polygon)
    {
        basis::Polygon polygon;
        polygon.header.name = proto_polygon.header().name();
        polygon.header.frameId = proto_polygon.header().frameid();
        polygon.header.info = proto_polygon.header().info();
        for (const auto &proto_pt : proto_polygon.points())
        {
            polygon.points.emplace_back(basis::Vec2f(proto_pt.x(), proto_pt.y()));
        }
        return polygon;
    }

    basis::Polygon ProtoBufToPolygon(const std::string &buf)
    {
        return ProtoToPolygon(ParseProtoMsg<xviz_msgs::Polygon2f>(buf));
    }

    basis::PolygonArray ProtoToPolygonArray(const xviz_msgs::Polygon2fArray &proto_polygons)
    {
        basis::PolygonArray polygon_array;
        polygon_array.header.name = proto_polygons.header().name();
        polygon_array.header.frameId = proto_polygons.header().frameid();
        polygon_array.header.info = proto_polygons.header().info();
        for (const auto &polygon : proto_polygons.polygonarray())
        {
            polygon_array.polygons.emplace_back(ProtoToPolygon(polygon));
        }
        return polygon_array;
    }

    basis::PolygonArray ProtoBufToPolygonArray(const std::string &buf)
    {
        return ProtoToPolygonArray(ParseProtoMsg<xviz_msgs::Polygon2fArray>(buf));
    }

    basis::Circle ProtoToCircle(const xviz_msgs::Circle2f &proto_circle)
    {
        basis::Circle circle;
        circle.header.name = proto_circle.header().name();
        circle.header.frameId = proto_circle.header().frameid();
        circle.header.info = proto_circle.header().info();
        circle.center.x = proto_circle.center().x();
        circle.center.y = proto_circle.center().y();
        circle.radius = proto_circle.radius();
        return circle;
    }

    basis::Circle ProtoBufToCircle(const std::string &buf)
    {
        return ProtoToCircle(ParseProtoMsg<xviz_msgs::Circle2f>(buf));
    }

    basis::CircleArray ProtoToCircleArray(const xviz_msgs::Circle2fArray &proto_circles)
    {
        basis::CircleArray circle_array;
        circle_array.header.name = proto_circles.header().name();
        circle_array.header.frameId = proto_circles.header().frameid();
        circle_array.header.info = proto_circles.header().info();
        for (const auto &circle : proto_circles.circlearray())
        {
            circle_array.circles.emplace_back(ProtoToCircle(circle));
        }
        return circle_array;
    }

    basis::CircleArray ProtoBufToCircleArray(const std::string &buf)
    {
        return ProtoToCircleArray(ParseProtoMsg<xviz_msgs::Circle2fArray>(buf));
    }

    basis::PointCloud ProtoToPointCloud(const xviz_msgs::PointCloud2f &proto_points)
    {
        basis::PointCloud point_cloud;
        point_cloud.header.name = proto_points.header().name();
        point_cloud.header.frameId = proto_points.header().frameid();
        point_cloud.header.info = proto_points.header().info();
        for (const auto &point : proto_points.points())
        {
            point_cloud.points.emplace_back(basis::Vec2f(point.x(), point.y()));
        }
        return point_cloud;
    }

    basis::PointCloud ProtoBufToPointCloud(const std::string &buf)
    {
        return ProtoToPointCloud(ParseProtoMsg<xviz_msgs::PointCloud2f>(buf));
    }

    basis::TransformNode ProtoToTransformNode(const xviz_msgs::Transform2fNode &transform)
    {
        basis::TransformNode transform_node;
        transform_node.header.name = transform.header().name();
        transform_node.header.frameId = transform.header().frameid();
        transform_node.frameId = transform.frameid();
        transform_node.parentFrameId = transform.parentframeid();
        transform_node.trans.x = transform.trans().x();
        transform_node.trans.y = transform.trans().y();
        transform_node.yaw = transform.angle();

        return transform_node;
    }

    basis::TransformNode ProtoBufToTransformNode(const std::string &buf)
    {
        return ProtoToTransformNode(ParseProtoMsg<xviz_msgs::Transform2fNode>(buf));
    }

}