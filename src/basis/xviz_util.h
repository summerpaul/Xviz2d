/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 15:09:49
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 17:37:47
 */
#include <stdint.h>

#ifndef __XVIZ_UTIL_H__
#define __XVIZ_UTIL_H__

#include "transform.h"
#include "xviz_math.h"
#include <string>
#include <chrono>
#include <ctime>

namespace basis
{
    

    inline std::string FormatDoubleValue(double val, int fixed)
    {
        std::string str = std::to_string(val);
        return str.substr(0, str.find('.') + fixed + 1);
    }

    inline std::string FormatFloatValue(float val, int fixed)
    {
        std::string str = std::to_string(val);
        return str.substr(0, str.find('.') + fixed + 1);
    }

    inline std::string GetFileTag(const std::string &file)
    {
        return file.substr(file.find_last_of('.') + 1);
    }

    inline std::string GetFileName(const std::string &file)
    {
        std::string::size_type iPos = (file.find_last_of('\\') + 1) == 0 ? file.find_last_of('/') + 1 : file.find_last_of('\\') + 1;
        std::string fileName = file.substr(iPos, file.length() - iPos);
        return fileName.substr(0, fileName.rfind('.'));
    }

    inline std::string GetFilePath(const std::string &file)
    {
        std::string::size_type iPos = (file.find_last_of('\\') + 1) == 0 ? file.find_last_of('/') + 1 : file.find_last_of('\\') + 1;
        return file.substr(0, iPos);
    }

    template <typename T>
    inline T RandomRange(T min, T max)
    {
        T scale = rand() / (T)RAND_MAX;
        return min + scale * (max - min);
    }

    inline void GenRectangle(const float pose_left_x, const float pose_top_y, const float pose_right_x, const float pose_bottom_y, Points &points)
    {
        points.clear();
        points.emplace_back(pose_left_x, pose_top_y);     // p0
        points.emplace_back(pose_right_x, pose_top_y);    // p1
        points.emplace_back(pose_right_x, pose_bottom_y); // p2
        points.emplace_back(pose_left_x, pose_bottom_y);  // p2
    }

    inline void GenRectangle(const Vec2f &near_pt, const Vec2f &far_pt, Points &points)
    {
        const float pose_left_x = near_pt.x;
        const float pose_bottom_y = near_pt.y;
        const float pose_right_x = far_pt.x;
        const float pose_top_y = far_pt.y;
        GenRectangle(pose_left_x, pose_top_y, pose_right_x, pose_bottom_y, points);
    }

    inline void GenRectangle(const Vec2f &pose, const float width, const float height, Points &points, bool is_center_pose = false)
    {
        float pose_left_x = 0;
        float pose_top_y = 0;
        float pose_right_x = 0;
        float pose_bottom_y = 0;
        if (is_center_pose)
        {
            pose_left_x = pose.x - width * 0.5f;
            pose_bottom_y = pose.y - height * 0.5f;
            pose_right_x = pose.x + width * 0.5f;
            pose_top_y = pose.y + height * 0.5f;
        }
        else
        {
            pose_left_x = pose.x;
            pose_bottom_y = pose.y;
            pose_right_x = pose.x + width;
            pose_top_y = pose.y + height;
        }

        GenRectangle(pose_left_x, pose_top_y, pose_right_x, pose_bottom_y, points);
    }

    template <typename Path>
    inline void GetPointsFromPath(const Path &path_in, const int pt_num, Points &points, const float ratio = 1.0f)
    {
        points.clear();
        points.resize(pt_num);
        for (int i = 0; i < pt_num; i++)
        {
            const float x = path_in[i].x * ratio;
            const float y = path_in[i].y * ratio;
            points[i] = Vec2f(x, y);
        }
    }
} // namespace basis

#endif /* __XVIZ_UTIL_H__ */
