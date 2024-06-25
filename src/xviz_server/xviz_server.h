/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-21 22:53:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-25 15:53:14
 */
#include <stdint.h>

#ifndef __XVIZ_SERVER_H__
#define __XVIZ_SERVER_H__
#include <future>
#include <thread>



namespace zmq
{
    class context_t;
    class socket_t;
}
namespace scene
{
    class SceneManager;
}

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
        std::unique_ptr<zmq::context_t> m_pCtx;
        std::unique_ptr<zmq::socket_t> m_pSub;
        std::unique_ptr<zmq::socket_t> m_pPub;
        std::thread m_receiveThread;
        const std::string m_subConnect = "tcp://127.0.0.1:8888";
        const std::string m_pubConnect = "tcp://127.0.0.1:8899";
        std::mutex m_mtx;
        bool m_running;
        std::shared_ptr<scene::SceneManager> m_pScene;
    };

} // namespace xviz_server

#endif /* __XVIZ_SERVER_H__ */
