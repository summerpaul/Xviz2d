/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-21 22:53:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 21:03:29
 */
#include "xviz_server.h"

#include <iostream>

#include "app/app.h"
#include "basis/defines.h"
#include "basis/logger.h"
#include "msg_convert/msg_convert.h"
using namespace std;

namespace xviz_server
{
    XvizServer::XvizServer() : m_running(false)
    {
        m_pCtx = std::make_unique<zmq::context_t>();

        m_pSub = std::make_unique<zmq::socket_t>(*m_pCtx, zmq::socket_type::sub);

        m_pPub = std::make_unique<zmq::socket_t>(*m_pCtx, zmq::socket_type::pub);
    }
    XvizServer::~XvizServer() { Disconnect(); }

    bool XvizServer::Init()
    {
        m_pScene = app::App::GetInstance()->GetSceneManager();
        return true;
    }

    bool XvizServer::Connect()
    {
        if (m_running)
        {
            LOG_WARN("Communication is already running");
            return m_running;
        }

        m_pSub->connect(m_subConnect);
        m_pSub->set(zmq::sockopt::rcvtimeo, 100);
        m_pSub->set(zmq::sockopt::subscribe, "");
        m_pPub->connect(m_pubConnect);
        m_receiveThread = std::thread(&XvizServer::ReceiveLoop, this);
        m_running = true;
        LOG_INFO("Connected");
        return m_running;
    }

    void XvizServer::Disconnect()
    {
        LOG_INFO("m_running is %d", m_running);
        if (m_running)
        {
            m_running = false;
            if (m_receiveThread.joinable())
            {
                LOG_INFO("receive thread joined");
                m_receiveThread.join();
                LOG_INFO("stop thread ");
            }

            if (m_pPub->handle() != nullptr)
            {
                m_pPub->disconnect(m_pubConnect.c_str());
                LOG_INFO("disconnect %s", m_pubConnect.c_str());
            }

            if (m_pSub->handle() != nullptr)
            {
                m_pSub->disconnect(m_subConnect.c_str());
                LOG_INFO("disconnect %s", m_subConnect.c_str());
            }
        }

        LOG_INFO("Disconnected");
    }
    bool XvizServer::IsConnected() { return m_running; }
    void XvizServer::ReceiveLoop()
    {

        while (m_running)
        {
            zmq::multipart_t recv_msgs;
            zmq::recv_result_t result =
                zmq::recv_multipart(*m_pSub, std::back_inserter(recv_msgs));
            CHECK_CONTINUE((recv_msgs.size() > 2 && result.has_value()));
            int msgType = std::stoi(recv_msgs[0].to_string());
            const std::string name = recv_msgs[1].to_string();
            const std::string data = recv_msgs[2].to_string();

            switch (msgType)
            {
            case MSG_TYPE::PATH2F:
            {
                auto path = xviz_msgs::ProtoBufToPath(data);
                m_pScene->AddPath(name, &path);
            }
            break;
            case MSG_TYPE::PATH2F_ARRAY:
            {
                auto paths = xviz_msgs::ProtoBufToPathArray(data);
                m_pScene->AddPathArray(name, &paths);
            }
            break;
            case MSG_TYPE::POSE2F:
            {
                auto pose = xviz_msgs::ProtoBufToPose(data);
                m_pScene->AddPose(name, &pose);
            }
            break;
            case MSG_TYPE::POSE2F_ARRAY:
            {
                auto poses = xviz_msgs::ProtoBufToPoseArray(data);
                m_pScene->AddPoseArray(name, &poses);
            }
            break;
            case MSG_TYPE::POINT_CLOUD2F:
            {
                auto point_cloud = xviz_msgs::ProtoBufToPointCloud(data);
                m_pScene->AddPointCloud(name, &point_cloud);
            }
            break;
            case MSG_TYPE::POLYGON2F:
            {
                auto polygon = xviz_msgs::ProtoBufToPolygon(data);
                m_pScene->AddPolygon(name, &polygon);
            }
            break;
            case MSG_TYPE::POLYGON2F_ARRAY:
            {
                auto polygons = xviz_msgs::ProtoBufToPolygonArray(data);
                m_pScene->AddPolygonArray(name, &polygons);
            }
            break;
            case MSG_TYPE::CIRCLE2F:
            {
                auto circle = xviz_msgs::ProtoBufToCircle(data);
                m_pScene->AddCircle(name, &circle);
            }
            break;
            case MSG_TYPE::CIRCLE2F_ARRAY:
            {
                auto circles = xviz_msgs::ProtoBufToCircleArray(data);
                m_pScene->AddCircleArray(name, &circles);
            }
            break;
            case MSG_TYPE::DOUBLE_DATA:
            {
                xviz_msgs::MapDouble proto_double_datas;
                proto_double_datas.ParseFromString(data);
                const double t = proto_double_datas.t();
                for (const auto &proto_double_data : proto_double_datas.data())
                {
                    m_pScene->AddDoubleData(proto_double_data.first, t, proto_double_data.second);
                }
            }
            break;
            case MSG_TYPE::STRING_DATA:
            {
                xviz_msgs::MapString proto_string_datas;
                proto_string_datas.ParseFromString(data);

                for (const auto &proto_string_data : proto_string_datas.data())
                {
                    m_pScene->AddStringData(proto_string_data.first, proto_string_data.second);
                }
            }
            break;

            default:
                break;
            }
        }
    }

} // namespace xviz_server