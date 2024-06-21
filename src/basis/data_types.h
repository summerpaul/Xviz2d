/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-27 19:24:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-21 23:21:06
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <memory>
#include <string>
#include <vector>
namespace basis
{

    const std::string MSG_PATH2F = "MSG_PATH2F";
    const std::string MSG_PATH2F_ARRAY = "MSG_PATH2F_ARRAY";
    const std::string MSG_POSE2F = "MSG_POSE2F";
    const std::string MSG_POSE2F_ARRAY = "MSG_POSE2F_ARRAY";
    const std::string MSG_POINT_CLOUD2F = "MSG_POINT_CLOUD2F";
    const std::string MSG_POLYGON2F = "MSG_POLYGON2F";
    const std::string MSG_POLYGON2F_ARRAY = "MSG_POLYGON2F_ARRAY";
    const std::string MSG_CIRCLE2F = "MSG_CIRCLE2F";
    const std::string MSG_CIRCLE2F_ARRAY = "MSG_CIRCLE2F_ARRAY";
    const std::string MSG_MARKER2F = "MSG_MARKER2F";
    const std::string MSG_MARKER2F_ARRAY = "MSG_MARKER2F_ARRAY";
    const std::string MSG_STRING_DATA = "MSG_STRING_DATA";
    const std::string MSG_DOUBLE_DATA = "MSG_DOUBLE_DATA";
    const std::string MSG_TRANSFORM2F_NODE = "MSG_TRANSFORM2F_NODE";

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
    };

    using Points = std::vector<Vec2f>;

    struct Path : public BaseObject
    {
        typedef std::shared_ptr<Path> Ptr;
        Path() {}
        Points points;
        bool isDashed = false;
        float thicknessScale = 1.0f;
        float dashLength = 0.5f;
        float gapLength = 0.1f;
    };

    struct PathArray : public BaseObject
    {
        typedef std::shared_ptr<PathArray> Ptr;
        PathArray() {}
        std::vector<Path> paths;
    };

    struct Polygon : public BaseObject
    {
        typedef std::shared_ptr<Polygon> Ptr;
        Polygon() {}
        Points points;
        bool filled = false;
    };

    struct PolygonArray : public BaseObject
    {
        typedef std::shared_ptr<PolygonArray> Ptr;
        PolygonArray() {}
        std::vector<Polygon> polygons;
    };

    struct Circle : public BaseObject
    {
        typedef std::shared_ptr<Circle> Ptr;
        Circle() {}
        Vec2f center;
        float radius;
    };

    struct CircleArray : public BaseObject
    {
        typedef std::shared_ptr<CircleArray> Ptr;
        CircleArray() {}
        std::vector<Circle> circles;
    };

    struct PointCloud : public BaseObject
    {
        typedef std::shared_ptr<PointCloud> Ptr;
        PointCloud() {}
        Points points;
    };

    struct Pose : public BaseObject
    {
        typedef std::shared_ptr<Pose> Ptr;
        Pose() {}
        Vec2f pos;
        float yaw = 0;
    };
    struct PoseArray : public BaseObject
    {
        typedef std::shared_ptr<PoseArray> Ptr;
        PoseArray() {}
        std::vector<Pose> poses;
    };

    struct TransformNode : public BaseObject
    {
        typedef std::shared_ptr<TransformNode> Ptr;
        TransformNode()
            : trans(Vec2f(0.0f, 0.0f)),
              yaw(0.0f),
              frameId(WORLD_FRAME),
              parentFrameId(ROOT_FRAME) {}

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
        SLATE_GRAY
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
        Marker() {}
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
        MarkerArray() {}
        std::vector<Marker> markers;
    };

} // namespace basis

#endif /* __DATA_TYPES_H__ */
