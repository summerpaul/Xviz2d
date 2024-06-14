/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:05:14
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:05:25
 */
#include <stdint.h>

#ifndef __ROLLING_BUFFER_H__
#define __ROLLING_BUFFER_H__

#include <deque>
#include <mutex>
#include <string>
#include <vector>
#include <imgui.h>
namespace scene
{

    struct RollingBuffer
    {
        double span = 100000;
        std::vector<double> xs;
        std::vector<double> ys;

        std::mutex mutex;
        ImVec4 color;
        int yax{};
        int idx{};
        bool isPlt = false;
        bool isStair = true;
        bool isMarkers = false;
        int lastMid = -1;

        float thickness = 1;
        std::string plotChartName;
        RollingBuffer()
        {
            span = 10000.0;
            xs.reserve(4000);
            ys.reserve(4000);
        }

        void AddPoint(double x, double y)
        {
            std::lock_guard<std::mutex> mtx(mutex);
            double xmod = fmod(x, span);
 /*           if (!xs.empty() && xmod < xs.back())
            {
                xs.clear();
                ys.clear();
            }*/
            xs.push_back(xmod);
            ys.push_back(y);
        }

        void Erase()
        {
            std::lock_guard<std::mutex> mtx(mutex);
            xs.clear();
            ys.clear();
        }
    };

} // namespace scene

#endif /* __ROLLING_BUFFER_H__ */
