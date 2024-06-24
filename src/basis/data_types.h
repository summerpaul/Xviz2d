/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-27 19:24:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-24 16:10:38
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <memory>
#include <string>
#include <vector>
namespace basis
{

    enum MSG_TYPE
    {
        PATH2F = 0,
        PATH2F_ARRAY,
        POSE2F,
        POSE2F_ARRAY,
        POINT_CLOUD2F,
        POLYGON2F,
        POLYGON2F_ARRAY,
        CIRCLE2F,
        CIRCLE2F_ARRAY,
        MARKER2F,
        MARKER2F_ARRAY,
        STRING_DATA,
        DOUBLE_DATA,
        TRANSFORM2F_NODE,
        UNKOWN
    };

    const std::string ROOT_FRAME = "root";
    const std::string WORLD_FRAME = "world";
    const std::string BASE_LINK = "base_link";
    const std::string BASE_LINK2 = "base_link2";
    const float EPSILONG = 1e-6f;

    struct Header
    {
        Header(const std::string &name = "",
               const std::string &frame_id = WORLD_FRAME,
               const std::string &info = "")
            : name(name), frameId(frame_id), info(info) {}

        std::string name = "";
        std::string frameId = WORLD_FRAME;
        std::string info;
    };

    struct Vec2f
    {
        Vec2f(float x = 0, float y = 0) : x(x), y(y) {}
        void SetZero()
        {
            x = 0;
            y = 0;
        }
        float x{0}, y{0};
    };

    struct Vec2i
    {
        Vec2i(int x = 0, int y = 0) : x(x), y(y) {}
        int x{0}, y{0};
    };

    struct BaseObject
    {
        typedef std::shared_ptr<BaseObject> Ptr;
        BaseObject() {}
        virtual ~BaseObject() {}
        virtual void clear() {}
        Header header{};
        bool isValid = true;
        bool useSelfColor = false;
        bool isSelfShowInfo = false;
        unsigned int color = 0;
        int data_type = MSG_TYPE::UNKOWN;
    };

    using Points = std::vector<Vec2f>;

    struct Path : public BaseObject
    {
        typedef std::shared_ptr<Path> Ptr;
        Path()
        {
            data_type = MSG_TYPE::PATH2F;
        }
        Points points;
        bool isDashed = false;
        float thicknessScale = 1.0f;
        float dashLength = 0.5f;
        float gapLength = 0.1f;
    };

    struct PathArray : public BaseObject
    {
        typedef std::shared_ptr<PathArray> Ptr;
        PathArray()
        {
            data_type = MSG_TYPE::PATH2F_ARRAY;
        }
        std::vector<Path> paths;
    };

    struct Polygon : public BaseObject
    {
        typedef std::shared_ptr<Polygon> Ptr;
        Polygon()
        {
            data_type = MSG_TYPE::POLYGON2F;
        }
        Points points;
        bool filled = false;
    };

    struct PolygonArray : public BaseObject
    {
        typedef std::shared_ptr<PolygonArray> Ptr;
        PolygonArray()
        {
            data_type = MSG_TYPE::POLYGON2F_ARRAY;
        }
        std::vector<Polygon> polygons;
    };

    struct Circle : public BaseObject
    {
        typedef std::shared_ptr<Circle> Ptr;
        Circle()
        {
            data_type = MSG_TYPE::CIRCLE2F;
        }
        Vec2f center;
        float radius;
    };

    struct CircleArray : public BaseObject
    {
        typedef std::shared_ptr<CircleArray> Ptr;
        CircleArray()
        {
            data_type = MSG_TYPE::CIRCLE2F_ARRAY;
        }
        std::vector<Circle> circles;
    };

    struct PointCloud : public BaseObject
    {
        typedef std::shared_ptr<PointCloud> Ptr;
        PointCloud()
        {
            data_type = MSG_TYPE::POINT_CLOUD2F;
        }
        Points points;
    };

    struct Pose : public BaseObject
    {
        typedef std::shared_ptr<Pose> Ptr;
        Pose()
        {
            data_type = MSG_TYPE::POSE2F;
        }
        Pose(float x, float y, float yaw) : pos(x, y), yaw(yaw)
        {
            data_type = MSG_TYPE::POSE2F;
        }
        Vec2f pos;
        float yaw = 0;
    };
    struct PoseArray : public BaseObject
    {
        typedef std::shared_ptr<PoseArray> Ptr;
        PoseArray()
        {
            data_type = MSG_TYPE::POSE2F_ARRAY;
        }
        std::vector<Pose> poses;
    };

    struct TransformNode : public BaseObject
    {
        typedef std::shared_ptr<TransformNode> Ptr;
        TransformNode()
            : trans(Vec2f(0.0f, 0.0f)),
              yaw(0.0f),
              frameId(WORLD_FRAME),
              parentFrameId(ROOT_FRAME)
        {
            data_type = MSG_TYPE::TRANSFORM2F_NODE;
        }

        Vec2f trans;
        float yaw;
        std::string frameId;
        std::string parentFrameId = ROOT_FRAME;
    };
    enum COLOR_TYPE
    {
        WHITE = 0,
        RED,
        GREEN,
        BLUE,
        BLACK,
        YELLOW,
        CYAN,
        MAGENTA,
        GRAY,
        PURPLE,
        PINK,
        LIGHT_BLUE,
        LIME_GREEN,
        SLATE_GRAY,
        ORANGE
    };

    enum MARKER_TYPE
    {
        PATH = 0,
        POLYGON = 1,
        CIRCLE = 3,
        POSE = 4,
        POINT_CLOUD = 5,
        NONE_TYPE
    };

    struct Marker : public BaseObject
    {
        typedef std::shared_ptr<Marker> Ptr;
        Marker()
        {
            data_type = MSG_TYPE::MARKER2F;
        }
        int type = 0;
        COLOR_TYPE color = COLOR_TYPE::BLACK;
        Path path;
        Polygon polygon;
        Circle circle;
        Pose pose;
        PointCloud pointCloud;
        float length = 1.0f;
        float thickness = 0.01f;
        float radius = 0.0f;
    };

    struct MarkerArray : public BaseObject
    {
        typedef std::shared_ptr<MarkerArray> Ptr;
        MarkerArray()
        {
            data_type = MSG_TYPE::MARKER2F_ARRAY;
        }
        std::vector<Marker> markers;
    };

} // namespace basis

#endif /* __DATA_TYPES_H__ */
