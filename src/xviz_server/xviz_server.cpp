/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-21 22:53:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-21 23:20:24
 */
#include "xviz_server.h"

#include <iostream>

#include "app/app.h"
#include "basis/defines.h"
#include "basis/logger.h"
using namespace std;

namespace xviz_server
{
    XvizServer::XvizServer() : m_running(false)
    {
        m_ctx = std::make_unique<zmq::context_t>();

        m_sub = std::make_unique<zmq::socket_t>(*m_ctx, zmq::socket_type::sub);

        m_pub = std::make_unique<zmq::socket_t>(*m_ctx, zmq::socket_type::pub);
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
        const std::string connectIP = "127.0.0.1";
        const std::string sub_port = "8888";

        const std::string pub_port = "8899";

        m_subConnect = "tcp://" + connectIP + ":" + sub_port;
        m_sub->connect(m_subConnect);
        m_sub->set(zmq::sockopt::rcvtimeo, 100);
        m_sub->set(zmq::sockopt::subscribe, "");
        m_pubConnect = "tcp://" + connectIP + ":" + pub_port;
        m_pub->connect(m_pubConnect);
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

            if (m_pub->handle() != nullptr)
            {
                m_pub->disconnect(m_pubConnect.c_str());
                LOG_INFO("disconnect %s", m_pubConnect.c_str());
            }

            if (m_sub->handle() != nullptr)
            {
                m_sub->disconnect(m_subConnect.c_str());
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
                zmq::recv_multipart(*m_sub, std::back_inserter(recv_msgs));
            CHECK_CONTINUE((recv_msgs.size() > 2 && result.has_value()));
            const std::string msgType = recv_msgs[0].to_string();
            const std::string name = recv_msgs[1].to_string();
            const std::string data = recv_msgs[2].to_string();
        }
    }

} // namespace xviz_server