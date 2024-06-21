/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-21 22:53:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-21 23:20:27
 */
#include <stdint.h>

#ifndef __XVIZ_SERVER_H__
#define __XVIZ_SERVER_H__
#include <future>
#include <thread>
#include <zmq.hpp>
#include <zmq_addon.hpp>

#include "scene/scene_manager.h"
#include "xviz_msgs/pb/xviz_msgs.pb.h"

namespace xviz_server
{
    class XvizServer
    {
    public:
        XvizServer();
        ~XvizServer();
        bool Init();
        void Disconnect();
        bool Connect();
        bool IsConnected();

    private:
        void ReceiveLoop();

    private:
        std::unique_ptr<zmq::context_t> m_ctx;
        std::unique_ptr<zmq::socket_t> m_sub;
        std::unique_ptr<zmq::socket_t> m_pub;
        std::thread m_receiveThread;
        std::string m_subConnect;
        std::string m_pubConnect;
        std::mutex m_mtx;
        bool m_running;
        std::shared_ptr<scene::SceneManager> m_pScene;
    };

} // namespace xviz_server

#endif /* __XVIZ_SERVER_H__ */
