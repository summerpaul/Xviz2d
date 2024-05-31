/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 15:08:30
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:39:08
 */
#include <stdint.h>

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "data_types.h"
#include "xviz_math.h"

namespace basis
{
    struct Rot
    {
        Rot() = default;

        explicit Rot(float angle)
        {
            m_sin = sinf(angle);
            m_cos = cosf(angle);
        }

        void Set(float angle)
        {

            m_sin = sinf(angle);
            m_cos = cosf(angle);
        }

        void SetIdentity()
        {
            m_sin = 0.0f;
            m_cos = 1.0f;
        }

        float GetAngle() const
        {
            return atan2f(m_sin, m_cos);
        }

        Vec2f GetXAxis() const
        {
            return {m_cos, m_sin};
        }

        Vec2f GetYAxis() const
        {
            return {-m_sin, m_cos};
        }

        float m_sin = 0.0f;
        float m_cos = 1.0f;
    };

    struct Transform
    {
        Transform() { SetIdentity(); }
        Transform(float x, float y, float angle) { Set(Vec2f(x, y), angle); }
        Transform(const Vec2f &position, float angle) : trans(position), rot(angle) {}
        Transform(const Vec2f &position, const Rot &rotation) : trans(position), rot(rotation) {}

        void SetIdentity()
        {
            trans.SetZero();
            rot.SetIdentity();
        }

        void Set(const Vec2f &position, float angle)
        {
            trans = position;
            rot.Set(angle);
        }

        Transform Inv() const
        {
            float inv_angle = -rot.GetAngle();
            float inv_x = -trans.x * rot.m_cos - trans.y * rot.m_sin;
            float inv_y = trans.x * rot.m_sin - trans.y * rot.m_cos;
            return {inv_x, inv_y, inv_angle};
        }

        Vec2f trans;
        Rot rot;
    };

    inline Rot Mul(const Rot &q, const Rot &r)
    {

        Rot qr;
        qr.m_sin = q.m_sin * r.m_cos + q.m_cos * r.m_sin;
        qr.m_cos = q.m_cos * r.m_cos - q.m_sin * r.m_sin;
        return qr;
    }

    inline Rot MulT(const Rot &q, const Rot &r)
    {

        Rot qr;
        qr.m_sin = q.m_cos * r.m_sin - q.m_sin * r.m_cos;
        qr.m_cos = q.m_cos * r.m_cos + q.m_sin * r.m_sin;
        return qr;
    }

    inline Vec2f Mul(const Rot &q, const Vec2f &v)
    {
        return {q.m_cos * v.x - q.m_sin * v.y, q.m_sin * v.x + q.m_cos * v.y};
    }

    inline Points Mul(const Rot &q, const Points &vs)
    {
        Points result;
        const size_t pt_size = vs.size();
        result.resize(pt_size);
        for (size_t i = 0; i < pt_size; i++)
        {
            result[i] = Mul(q, vs[i]);
        }
        return result;
    }

    inline Vec2f MulT(const Rot &q, const Vec2f &v)
    {
        return {q.m_cos * v.x + q.m_sin * v.y, -q.m_sin * v.x + q.m_cos * v.y};
    }

    inline Vec2f Mul(const Transform &T, const Vec2f &v)
    {
        float x = (T.rot.m_cos * v.x - T.rot.m_sin * v.y) + T.trans.x;
        float y = (T.rot.m_sin * v.x + T.rot.m_cos * v.y) + T.trans.y;

        return {x, y};
    }

    inline Vec2f MulT(const Transform &T, const Vec2f &v)
    {
        float px = v.x - T.trans.x;
        float py = v.y - T.trans.y;
        float x = (T.rot.m_cos * px + T.rot.m_sin * py);
        float y = (-T.rot.m_sin * px + T.rot.m_cos * py);

        return {x, y};
    }

    inline Points Mul(const Transform &T, const Points &vs)
    {
        Points result;
        const size_t pt_size = vs.size();
        result.resize(pt_size);
        for (size_t i = 0; i < pt_size; i++)
        {
            result[i] = Mul(T, vs[i]);
        }
        return result;
    }

    inline Points MulT(const Transform &T, const Points &vs)
    {
        Points result;
        const size_t pt_size = vs.size();
        result.resize(pt_size);
        for (size_t i = 0; i < pt_size; i++)
        {
            result[i] = Mul(T, vs[i]);
        }
        return result;
    }

    inline Transform Mul(const Transform &A, const Transform &B)
    {
        Transform C;
        C.rot = Mul(A.rot, B.rot);
        C.trans = Mul(A.rot, B.trans) + A.trans;
        return C;
    }

    inline Transform MulT(const Transform &A, const Transform &B)
    {
        Transform C;
        C.rot = MulT(A.rot, B.rot);
        C.trans = MulT(A.rot, B.trans - A.trans);
        return C;
    }

    inline Transform PoseToTransform(const Pose &pose)
    {
        return Transform(pose.pos, pose.yaw);
    }

    inline Pose TransformToPose(const Transform &transform)
    {
        Pose pose;
        pose.pos = transform.trans;
        pose.yaw = transform.rot.GetAngle();
        return pose;
    }

    inline Pose TransformToPose(const Vec2f &trans, float angle)
    {
        Pose pose;
        pose.pos = trans;
        pose.yaw = angle;
        return pose;
    }

    inline Pose Mul(const Transform &A, const Pose &pose)
    {
        Transform B = PoseToTransform(pose);
        return TransformToPose(Mul(A, B));
    }

    inline Pose MulT(const Transform &A, const Pose &pose)
    {
        Transform B = PoseToTransform(pose);
        return TransformToPose(MulT(A, B));
    }

} // namespace basis

#endif /* __TRANSFORM_H__ */
