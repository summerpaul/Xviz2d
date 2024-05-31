/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 15:04:48
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 15:08:01
 */
#include <stdint.h>

#ifndef __XVIZ_MATH_H__
#define __XVIZ_MATH_H__
#include <cmath>
#include "data_types.h"
#include "defines.h"
namespace basis
{
    template <typename T>
    static int Sign(T num)
    {
        return (T(0) < num) - (num < T(0));
    }

    template <typename T>
    static T NormalizeAngleDeg(T deg)
    {
        while (deg > 180)
            deg -= 360;
        while (deg < -180)
            deg += 360;
        return deg;
    }

    template <typename T>
    static T NormalizeAngleRad(T rad)
    {
        while (rad > XVIZ_PI)
            rad -= XVIZ_2PI;
        while (rad < -XVIZ_PI)
            rad += XVIZ_2PI;
        return rad;
    }

    static inline Vec2f Vec2fLerp(const Vec2f &a, const Vec2f &b, float t)
    {
        return Vec2f(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }

    // 向量长度
    static float Length(const Vec2f &v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    static float DistanceSquared(const Vec2f &v1, const Vec2f &v2)
    {
        return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
    }

    static float Distance(const Vec2f &v1, const Vec2f &v2)
    {
        return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
    }

    static float Dot(const Vec2f &v1, const Vec2f &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static float Cross(const Vec2f &v1, const Vec2f &v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

    static Vec2f operator+(const Vec2f &v1, const Vec2f &v2)
    {
        return Vec2f(v1.x + v2.x, v1.y + v2.y);
    }

    static Vec2f operator-(const Vec2f &v1, const Vec2f &v2)
    {
        return Vec2f(v1.x - v2.x, v1.y - v2.y);
    }

    static Vec2f operator*(const Vec2f &v1, float s)
    {
        return Vec2f(v1.x * s, v1.y * s);
    }

    static Vec2f operator*(float s, const Vec2f &v1)
    {
        return Vec2f(v1.x * s, v1.y * s);
    }

    static Vec2f operator/(const Vec2f &v1, float s)
    {
        return Vec2f(v1.x / s, v1.y / s);
    }

    static Vec2f Normalize(const Vec2f &v)
    {
        float len = Length(v);
        return Vec2f(v.x / len, v.y / len);
    }

    static float AngleDeg(const Vec2f &v1, const Vec2f &v2)
    {
        return std::atan2(Cross(v1, v2), Dot(v1, v2)) * XVIZ_RPI * 180;
    }

    static float AngleRad(const Vec2f &v1, const Vec2f &v2)
    {
        return std::atan2(Cross(v1, v2), Dot(v1, v2));
    }

    static Vec2f Rotate(const Vec2f &v, float rad)
    {
        return Vec2f(v.x * std::cos(rad) - v.y * std::sin(rad), v.x * std::sin(rad) + v.y * std::cos(rad));
    }

    static Points Rotate(const Points &points, float rad)
    {
        Points ret;
        ret.resize(points.size());
        for (size_t i = 0; i < points.size(); i++)
        {
            ret[i] = Rotate(points[i], rad);
        }
        return ret;
    }
} // namespace basis

#endif /* __XVIZ_MATH_H__ */
