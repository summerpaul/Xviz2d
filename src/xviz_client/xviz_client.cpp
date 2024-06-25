/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-25 10:52:51
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-25 16:17:16
 */
#include "xviz_client.h"
#include "msg_convert/msg_convert.h"
#include "basis/logger.h"

#include <zmq.hpp>
#include <zmq_addon.hpp>

namespace xviz_client
{
    XvizClient::XvizClient()
    {
    }
    XvizClient::~XvizClient() {}
    bool XvizClient::Init()
    {
        m_ctx = std::make_unique<zmq::context_t>();
        m_pub = std::make_unique<zmq::socket_t>(*m_ctx, zmq::socket_type::pub);
        m_sub = std::make_unique<zmq::socket_t>(*m_ctx, zmq::socket_type::sub);
        try
        {
            m_pub->bind(m_pubConnect);
        }
        catch (const std::exception &e)
        {
            LOG_FATAL("%s", e.what());
            return false;
        }

        try
        {
            m_sub->bind(m_subConnect);
        }
        catch (const std::exception &e)
        {
            LOG_FATAL("%s", e.what());

            return false;
        }
        return true;
    }
    void XvizClient::PubPath(const std::string &name, const Path &path)
    {
        PubProto(xviz_msgs::PathToProtoBuf(path), name, MSG_TYPE::PATH2F);
    }
    void XvizClient::PubPathArray(const std::string &name, const PathArray &pathArray)
    {
        PubProto(xviz_msgs::PathArrayToProtoBuf(pathArray), name, MSG_TYPE::PATH2F_ARRAY);
    }
    void XvizClient::PubPose(const std::string &name, const Pose &pose)
    {
        PubProto(xviz_msgs::PoseToProtoBuf(pose), name, MSG_TYPE::POSE2F);
    }
    void XvizClient::PubPoseArray(const std::string &name, const PoseArray &poseArray)
    {
        PubProto(xviz_msgs::PoseArrayToProtoBuf(poseArray), name, MSG_TYPE::POSE2F_ARRAY);
    }
    void XvizClient::PubPointCloud(const std::string &name, const PointCloud &pointCloud)
    {
        PubProto(xviz_msgs::PointCloudToProtoBuf(pointCloud), name, MSG_TYPE::POINT_CLOUD2F);
    }
    void XvizClient::PubPolygon(const std::string &name, const Polygon &polygon)
    {
        PubProto(xviz_msgs::PolygonToProtoBuf(polygon), name, MSG_TYPE::POLYGON2F);
    }
    void XvizClient::PubPolygonArray(const std::string &name, const PolygonArray &polygonArray)
    {
        PubProto(xviz_msgs::PolygonArrayToProtoBuf(polygonArray), name, MSG_TYPE::POLYGON2F_ARRAY);
    }
    void XvizClient::PubCircle(const std::string &name, const Circle &circle)
    {
        PubProto(xviz_msgs::CircleToProtoBuf(circle), name, MSG_TYPE::CIRCLE2F);
    }
    void XvizClient::PubCircleArray(const std::string &name, const CircleArray &circleArray)
    {
        PubProto(xviz_msgs::CircleArrayToProtoBuf(circleArray), name, MSG_TYPE::CIRCLE2F_ARRAY);
    }
    void XvizClient::PubMarker(const std::string &name, const Marker &marker)
    {
        // PubProto(xviz_msgs::MarkerToProtoBuf(marker), name, MSG_TYPE::MARKER2F);
    }
    void XvizClient::PubMarkerArray(const std::string &name, const MarkerArray &markerArray)
    {
        // PubProto(xviz_msgs::MarkerArrayToProtoBuf(markerArray), name, MSG_TYPE::MARKER2F_ARRAY);
    }
    void XvizClient::AddDoubleData(const std::string &name, double data)
    {
    }
    void XvizClient::AddStringData(const std::string &name, const std::string &data) {}

    void XvizClient::PubProto(const std::string &string_msg, const std::string &topic,
                              const int msg_type)
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        zmq::message_t target_msg;
        target_msg.rebuild(string_msg);
        m_pub->send(zmq::message_t(std::to_string(msg_type)), zmq::send_flags::sndmore);
        m_pub->send(zmq::message_t(topic), zmq::send_flags::sndmore);
        m_pub->send(target_msg, zmq::send_flags::dontwait);
    }

}
