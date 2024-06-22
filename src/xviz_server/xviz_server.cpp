/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-21 22:53:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 16:13:38
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
                break;
            case MSG_TYPE::PATH2F_ARRAY:
                break;
            case MSG_TYPE::POSE2F:
                break;
            case MSG_TYPE::POSE2F_ARRAY:
                break;
            case MSG_TYPE::POINT_CLOUD2F:
                break;
            case MSG_TYPE::POLYGON2F:
                break;
            case MSG_TYPE::POLYGON2F_ARRAY:
                break;
            case MSG_TYPE::CIRCLE2F:
                break;
            case MSG_TYPE::CIRCLE2F_ARRAY:
                break;
            case MSG_TYPE::DOUBLE_DATA:
                break;
            case MSG_TYPE::STRING_DATA:
                break;

            default:
                break;
            }
        }
    }

} // namespace xviz_server