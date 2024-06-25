/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-25 10:52:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-25 15:52:32
 */
#include <stdint.h>

#ifndef __XVIZ_CLIENT_H__
#define __XVIZ_CLIENT_H__

#include "basis/data_types.h"
#include <functional>
#include <memory>
#include <thread>
#include <map>
#include <fstream>
#include <mutex>
#include <string>
using namespace basis;

namespace zmq
{
    class context_t;
    class socket_t;
}

namespace xviz_client
{
    class XvizClient
    {
    public:
        XvizClient();
        ~XvizClient();
        bool Init();
        void PubPath(const std::string &name, const Path &path);
        void PubPathArray(const std::string &name, const PathArray &pathArray);
        void PubPose(const std::string &name, const Pose &pose);
        void PubPoseArray(const std::string &name, const PoseArray &poseArray);
        void PubPointCloud(const std::string &name, const PointCloud &pointCloud);
        void PubPolygon(const std::string &name, const Polygon &polygon);
        void PubPolygonArray(const std::string &name, const PolygonArray &polygonArray);
        void PubCircle(const std::string &name, const Circle &circle);
        void PubCircleArray(const std::string &name, const CircleArray &circleArray);
        void PubMarker(const std::string &name, const Marker &marker);
        void PubMarkerArray(const std::string &name, const MarkerArray &markerArray);
        void AddDoubleData(const std::string &name, double data);
        void AddStringData(const std::string &name, const std::string &data);


        private :
        void PubProto(const std::string& string_msg, const std::string &topic,
                                  const int msg_type);

    private:
        std::unique_ptr<zmq::context_t> m_ctx;
        std::unique_ptr<zmq::socket_t> m_pub;
        std::unique_ptr<zmq::socket_t> m_sub;
        std::map<std::string, double> m_doubleData;
        std::map<std::string, std::string> m_stringData;
        const std::string m_subConnect = "tcp://127.0.0.1:8899";
        const std::string m_pubConnect = "tcp://127.0.0.1:8888";
        std::mutex m_mtx;
    };

}

#endif /* __XVIZ_CLIENT_H__ */
