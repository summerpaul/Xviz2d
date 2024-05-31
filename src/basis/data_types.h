/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-27 19:24:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:37:33
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <string>
#include <vector>
namespace basis
{

    const std::string ROOT_FRAME = "root";
    const std::string WORLD_FRAME = "world";
    const std::string BASE_LINK = "base_link";
    const std::string BASE_LINK2 = "base_link2";
    const float EPSILONG = 1e-6f;

    struct Header
    {
        Header(const std::string &name = "",
               const std::string &frame_id = WORLD_FRAME)
            : name(name), frameId(frame_id)
        {
        }

        std::string name = "";
        std::string frameId = WORLD_FRAME;
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

    using Points = std::vector<Vec2f>;

    struct Path
    {
        Path() {}
        Header header{};
        Points points;
        bool isDashed = false;
        float thicknessScale = 1.0f;
        float dashLength = 0.5f;
        float gapLength = 0.1f;
        bool isValid = false;
    };

    struct PathArray
    {
        PathArray() {}

        Header header;
        std::vector<Path> paths;
        bool isValid = false;
    };

    struct Polygon
    {
        Polygon() {}

        Header header;
        Points points;
        bool filled = false;
        bool isValid = false;
    };

    struct PolygonArray
    {
        PolygonArray() {}

        Header header;
        std::vector<Polygon> polygons;
        bool isValid = false;
    };

    struct Circle
    {
        Circle() {}

        Header header;
        Vec2f center;
        float radius;
        bool isValid = false;
    };

    struct CircleArray
    {
        CircleArray() {}

        Header header;
        std::vector<Circle> circles;
        bool isValid = false;
    };

    struct PointCloud
    {
        PointCloud() {}

        Header header;
        Points points;
        bool isValid = false;
    };

    struct Pose
    {
        Pose() {}

        Header header;
        Vec2f pos;
        float yaw = 0;
        bool isValid = false;
    };
    struct PoseArray
    {
        PoseArray() {}

        Header header;
        std::vector<Pose> poses;
        bool isValid = false;
    };

    struct TransformNode
    {
        TransformNode() {}

        Vec2f trans;
        float yaw;
        std::string frameId;
        std::string parentFrameId = ROOT_FRAME;
        bool isValid = false;
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
    struct Marker
    {
        Marker() {}

        Header header;
        int type = 0;
        int color = 0;
        Path path;
        Polygon polygon;
        Circle circle;
        Pose pose;
        PointCloud pointCloud;
        float length = 1.0f;
        float thickness = 0.01f;
        float radius = 0.0f;
        bool isValid = false;
    };

    struct MarkerArray
    {
        MarkerArray() {}
        Header header;
        std::vector<Marker> markers;
        bool isValid = false;
    };

} // namespace basis

#endif /* __DATA_TYPES_H__ */
