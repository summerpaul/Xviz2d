/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-30 15:29:17
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 17:57:08
 */
#include <stdint.h>

#ifndef __DEMO_DRAW_H__
#define __DEMO_DRAW_H__

#include "basis/data_types.h"
#include "scene/scene_manager.h"
#include "scene/scene_color.h"
using namespace basis;
bool g_first_draw = true;

void DrawTransformDemo(const scene::SceneManager::Ptr &scene)
{

    TransformNode tf_node1;
    tf_node1.frameId = BASE_LINK;
    tf_node1.parentFrameId = WORLD_FRAME;
    tf_node1.trans = {5.0f, 5.0f};
    tf_node1.yaw = XVIZ_PI4;

    TransformNode tf_node2;
    tf_node2.frameId = BASE_LINK2;
    tf_node2.parentFrameId = BASE_LINK;
    tf_node2.trans = {10.0f, 10.0f};
    tf_node2.yaw = XVIZ_PI4;


    if (g_first_draw)
    {
        scene::SceneObjectOptions options;
        options.isShowID = false;
        options.length = 1.0f;

        scene->AddTransformNode(BASE_LINK, &tf_node1, &options);
        options.isShowID = true;
        options.length = 2.0f;
        scene->AddTransformNode(BASE_LINK2, &tf_node2, &options);
    }
    else
    {
        scene->AddTransformNode(BASE_LINK, &tf_node1);

        scene->AddTransformNode(BASE_LINK2, &tf_node2);
    }
}

// 绘制路径的demo
void DrawPathDemo(const scene::SceneManager::Ptr &scene)
{
    Path path;
    scene::SceneObjectOptions options;
    for (float s = 0; s < XVIZ_2PI; s += 0.05f)
    {
        path.points.emplace_back(Vec2f(s, sin(s)));
    }

    // path.header.name = "world_path";
    path.header.frameId = WORLD_FRAME;
    path.header.name = "world_path";
    options.color = scene::IM_BLUE;

    if (g_first_draw)
    {
        scene->AddPath("world_path", &path, &options);
    }
    else
    {
        scene->AddPath("world_path", &path);
    }

    path.header.frameId = BASE_LINK;
    path.header.name = "frameId1_path";
    scene->AddPath("frameId1_path", &path);
    path.header.frameId = BASE_LINK2;
    
    options.color = scene::IM_RED;
    options.isShowID = true;
    options.thickness = 0.02f;
    path.header.name = "frameId2_path";
    path.isDashed = true;
    if (g_first_draw)
    {
        scene->AddPath("frameId2_path", &path, &options);
    }
    else
    {
        scene->AddPath("frameId2_path", &path);
    }
}

void DrawPolygonDemo(const scene::SceneManager::Ptr &scene)
{
    Polygon polygon;
    polygon.header.frameId = WORLD_FRAME;

    Vec2f p0{0.0f, 0.0f}, p1{2.5f, 0.0f}, p2{2.5f, 2.5f}, p3{0.0f, 2.5f};
    polygon.points.emplace_back(p0);
    polygon.points.emplace_back(p1);
    polygon.points.emplace_back(p2);
    polygon.points.emplace_back(p3);
    polygon.header.name = "world_plygon";
    scene->AddPolygon("world_plygon", &polygon);
    polygon.header.frameId = BASE_LINK;
    polygon.header.name = "frame1_plygon";
    scene->AddPolygon("frame1_plygon", &polygon);

    polygon.header.frameId = BASE_LINK2;
    polygon.header.name = "frame2_plygon";
    scene->AddPolygon("frame2_plygon", &polygon);
}

void DrawPoseDemo(const scene::SceneManager::Ptr &scene)
{
    Pose pose;
    pose.header.frameId = WORLD_FRAME;
    pose.header.name = "world_pose";
    pose.pos.x = 10.0f;
    pose.pos.y = 10.0f;
    pose.yaw = XVIZ_PI4;
    scene->AddPose("world_pose", &pose);

    pose.header.name = "frame1_pose";
    pose.header.frameId = BASE_LINK;
    scene->AddPose("frame1_pose", &pose);

    pose.header.name = "frame2_pose";
    pose.header.frameId = BASE_LINK2;
    scene->AddPose("frame2_pose", &pose);
}

void DrawCircleDemo(const scene::SceneManager::Ptr &scene)
{
    Circle cricle;
    cricle.header.frameId = WORLD_FRAME;
    cricle.header.name = "world_cricle";
    cricle.center.x = 15.0f;
    cricle.center.y = 15.0f;
    cricle.radius = 5.0f;
    scene::SceneObjectOptions options;
    if (g_first_draw)
    {
        options.color = scene::IM_RED;

        scene->AddCircle("world_cricle", &cricle, &options);
    }
    else
    {
        scene->AddCircle("world_cricle", &cricle);
    }

    cricle.header.name = "frame1_cricle";
    cricle.header.frameId = BASE_LINK;
    scene->AddCircle("frame1_cricle", &cricle);
    cricle.header.name = "frame2_cricle";
    cricle.header.frameId = BASE_LINK2;
    scene->AddCircle("frame2_cricle", &cricle);
}

void DrawPointCloudDemo(const scene::SceneManager::Ptr &scene)
{
    PointCloud point_cloud;
    point_cloud.header.frameId = WORLD_FRAME;
    point_cloud.header.name = "world_point_cloud";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            point_cloud.points.emplace_back(Vec2f{0.5f * i, 0.5f * j});
        }
    }
    scene::SceneObjectOptions options;
    if (g_first_draw)
    {
        options.color = scene::IM_RED;
        scene->AddPointCloud("world_point_cloud", &point_cloud, &options);
    }
    else
    {
        scene->AddPointCloud("world_point_cloud", &point_cloud);
    }

    point_cloud.header.frameId = BASE_LINK;
    point_cloud.header.name = "frame1_point_cloud";
    scene->AddPointCloud("frame1_point_cloud", &point_cloud);
    point_cloud.header.frameId = BASE_LINK2;
    point_cloud.header.name = "frame2_point_cloud";
    scene->AddPointCloud("frame2_point_cloud", &point_cloud);
}

void DrawPathArrayDemo(const scene::SceneManager::Ptr &scene)
{

    Path path;
    for (float i = 0; i < 5; i += 0.02f)
    {
        Vec2f p;
        p.x = float(i);
        p.y = 2.0f * float(i);
        path.points.emplace_back(p);
    }
    Path path1, path2, path3;
    Transform tf1(1.0f, 1.0f, 0.5f * XVIZ_PI2);
    path1.points = Mul(tf1, path.points);

    path2.points = Mul(tf1, path1.points);
    path3.points = Mul(tf1, path2.points);
    path3.isDashed = true;
    path1.header.name = "path1";
    path2.header.name = "path2";
    path3.header.name = "path3";

    PathArray path_array;
    path_array.paths.resize(3);
    path_array.paths[0] = path1;
    path_array.paths[1] = path2;
    path_array.paths[2] = path3;
    path_array.header.frameId = WORLD_FRAME;
    path_array.header.name = "world_path_array";

    scene::SceneObjectOptions options;
    if (g_first_draw)
    {
        options.color = scene::IM_RED;
        scene->AddPathArray("world_path_array", &path_array, &options);
    }
    else
    {
        scene->AddPathArray("world_path_array", &path_array);
    }

    path_array.header.frameId = BASE_LINK;
    scene->AddPathArray("frame1_path_array", &path_array);
    path_array.header.frameId = BASE_LINK2;
    scene->AddPathArray("frame2_path_array", &path_array);
}

void DrawPolygonArrayDemo(const scene::SceneManager::Ptr &scene)
{
    Polygon polygon, polygon1, polygon2, polygon3;

    Vec2f p0{0.0f, 0.0f}, p1{2.5f, 0.0f}, p2{2.5f, 2.5f}, p3{0.0f, 2.5f};
    polygon.points.emplace_back(p0);
    polygon.points.emplace_back(p1);
    polygon.points.emplace_back(p2);
    polygon.points.emplace_back(p3);

    Transform tf1(1.0f, 1.0f, 0.5f * XVIZ_PI2);
    PolygonArray polygonArray;
    polygon1.points = Mul(tf1, polygon.points);
    polygon2.points = Mul(tf1, polygon1.points);
    polygon3.points = Mul(tf1, polygon2.points);

    polygon1.header.name = "polygon1";
    polygon2.header.name = "polygon2";
    polygon3.header.name = "polygon3";

    polygonArray.polygons.emplace_back(polygon1);
    polygonArray.polygons.emplace_back(polygon2);
    polygonArray.polygons.emplace_back(polygon3);
    polygonArray.header.frameId = WORLD_FRAME;

    scene::SceneObjectOptions options;
    if (g_first_draw)
    {
        options.color = scene::IM_RED;
        options.thickness = 0.05f;
        scene->AddPolygonArray("world_polygon_array", &polygonArray, &options);
    }
    else
    {
        scene->AddPolygonArray("world_polygon_array", &polygonArray);
    }

    scene->AddPolygonArray("world_polygon_array", &polygonArray);
    polygonArray.header.frameId = BASE_LINK;
    scene->AddPolygonArray("frame1_polygon_array", &polygonArray);
    polygonArray.header.frameId = BASE_LINK2;
    scene->AddPolygonArray("frame2_polygon_array", &polygonArray);
}

void AddDoubleDataDemo(const scene::SceneManager::Ptr &scene)
{
    float a1 = RandomRange(0.0f, 10.0f);
    float a2 = RandomRange(5.0f, 10.0f);
    float a3 = RandomRange(0.0f, 100.0f);
    float a4 = RandomRange(50.0f, 100.0f);
    float a5 = RandomRange(-500.0f, 500.0f);

    float b1 = 2.0f * a1;
    float b2 = 2.0f * a2;
    float b3 = 2.0f * a3;
    float b4 = 2.0f * a4;
    float b5 = 2.0f * a5;
    static double start_time = GetTimeNow();

    const double during_time = GetTimeNow() - start_time;
    scene->AddDoubleData("a1", during_time, a1);
    scene->AddDoubleData("a2", during_time, a2);
    scene->AddDoubleData("a3", during_time, a3);
    scene->AddDoubleData("a4", during_time, a4);
    scene->AddDoubleData("a5", during_time, a5);

    scene->AddDoubleData("b1", during_time, b1);
    scene->AddDoubleData("b2", during_time, b2);
    scene->AddDoubleData("b3", during_time, b3);
    scene->AddDoubleData("b4", during_time, b4);
    scene->AddDoubleData("b5", during_time, b5);
}

void SceneDemo(const scene::SceneManager::Ptr &scene)
{
    DrawTransformDemo(scene);
    DrawPathDemo(scene);
    DrawPolygonDemo(scene);
    DrawPoseDemo(scene);
    DrawCircleDemo(scene);
    DrawPointCloudDemo(scene);
    DrawPathArrayDemo(scene);
    DrawPolygonArrayDemo(scene);
    AddDoubleDataDemo(scene);
}

#endif /* __DEMO_DRAW_H__ */
