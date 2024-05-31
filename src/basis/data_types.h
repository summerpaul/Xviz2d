/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-27 19:24:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 00:14:20
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <string>
#include <vector>
#include <memory>
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

    struct BaseObject
    {
        typedef std::shared_ptr<BaseObject> Ptr;
        BaseObject() {}
        virtual void clear() {}
        Header header{};
        bool isValid = true;
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
        TransformNode() {}

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
        int color = 0;
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
