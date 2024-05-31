/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:17:01
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 00:46:43
 */

#include "scene_view.h"
#include "scene_draw.h"
#include "basis/xviz_math.h"
#include "basis/xviz_util.h"
#include "scene/tf_tree/tf_tree.h"
#include "scene/scene_options.h"
#include "basis/logger.h"
#include <memory>
#include <iostream>
namespace scene
{
    void DrawLine(ImDrawList *drawList, const SceneView::Ptr &view,
                  const Vec2f &p1, const Vec2f &p2, ImU32 col, float thickness = 0.02f)
    {
        auto pw1 = view->FromLocal(p1);
        auto pw2 = view->FromLocal(p2);
        auto pw_thickness = thickness * view->invScale;
        drawList->AddLine({pw1.x, pw1.y}, {pw2.x, pw2.y}, col, pw_thickness);
    }

    void DrawNgonFilled(ImDrawList *drawList, const SceneView::Ptr &view, const Vec2f &center, float radius, ImU32 col, int num_segments)
    {
        auto pw_center = view->FromLocal(center);
        auto pw_radius = radius * view->invScale;
        drawList->AddNgonFilled({pw_center.x, pw_center.y}, pw_radius, col, num_segments);
    }

    void DrawDashedLine(ImDrawList *drawList, const SceneView::Ptr &view, Vec2f p1, Vec2f p2, ImU32 color, float dashSize = 0.1f, float thickness = 0.02f)
    {
        const Vec2f diff = p2 - p1;
        const float length = Length(diff);
        const Vec2f dir = diff * (1.f / length);
        const int numDashes = static_cast<int>(length / dashSize + 0.5f);
        const float remainingLength = length - numDashes * dashSize;
        const float dashSpacing = remainingLength / (numDashes - 1);

        for (int i = 0; i < numDashes; ++i)
        {
            CHECK_CONTINUE(i % 2 == 0);
            const float start = i * dashSize + fminf(i * dashSpacing, remainingLength);
            const float end = fminf(start + dashSize, length);
            const Vec2f dashStart = p1 + dir * start;
            const Vec2f dashEnd = p1 + dir * end;
            DrawLine(drawList, view, dashStart, dashEnd, color, thickness);
        }
    }

    void DrawCircle(ImDrawList *drawList, const SceneView::Ptr &view, const Vec2f &center, float raduis, ImU32 col, float thickness = 0.02f)
    {
        auto pw_center = view->FromLocal(center);
        auto pw_radius = raduis * view->invScale;
        auto pw_thickness = thickness * view->invScale;
        drawList->AddCircle({pw_center.x, pw_center.y}, pw_radius, col, 0, pw_thickness);
    }

    void DrawPolyline(ImDrawList *drawList, const SceneView::Ptr &view, const Points &points, ImU32 col, bool is_polygon = false, float thickness = 0.02f)
    {
        size_t num_points = points.size();
        CHECK_RETURN(num_points == 0);
        if (is_polygon)
        {
            num_points += 1;
        }
        auto *pts = (ImVec2 *)malloc(num_points * sizeof(ImVec2));
        for (int i = 0; i < points.size(); i++)
        {
            auto pw = view->FromLocal(points[i]);
            pts[i] = {pw.x, pw.y};
        }
        if (is_polygon)
        {
            auto pw = view->FromLocal(points[0]);
            pts[num_points - 1] = {pw.x, pw.y};
        }
        auto pw_thickness = thickness * view->invScale;
        drawList->AddPolyline(pts, int(num_points), col, 0, pw_thickness);
        free(pts);
    }

    void DrawConvexPolyFilled(ImDrawList *drawList, const SceneView::Ptr &view, const Points &points, ImU32 col)
    {
        size_t num_points = points.size();
        CHECK_RETURN(num_points == 0);
        auto *pts = (ImVec2 *)malloc(num_points * sizeof(ImVec2));
        for (int i = 0; i < points.size(); i++)
        {
            auto pw = view->FromLocal(points[i]);
            pts[i] = {pw.x, pw.y};
        }
        drawList->AddConvexPolyFilled(pts, int(num_points), col);
        free(pts);
    }

    void DrawDashedPolyline(ImDrawList *draw_list, const SceneView::Ptr &view, const Points &points, ImU32 col, ImU32 backgraoud_color, float thickness, float dash_length, float gap_length)
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            DrawLine(draw_list, view, points[i], points[i + 1], col, thickness);

            // 插入虚线间隔
            if ((i % (int)(dash_length / gap_length)) == 0 && i + 1 < points.size() - 1)
            {
                Vec2f delta = points[i + 1] - points[i];
                Vec2f norm = Vec2f(delta.y, -delta.x);
                norm = norm * gap_length / 2.0f;

                Vec2f p1 = points[i] + norm;
                Vec2f p2 = points[i + 1] + norm;
                Vec2f p3 = points[i] - norm;
                Vec2f p4 = points[i + 1] - norm;
                // 绘制背景颜色
                DrawLine(draw_list, view, p1, p2, backgraoud_color, thickness);
                DrawLine(draw_list, view, p3, p4, backgraoud_color, thickness);
            }
        }
    }

    void DrawText(ImDrawList *drawList, const SceneView::Ptr &view, const Vec2f &pos, ImU32 col, const std::string &text)
    {
        Vec2f pixelPose = view->FromLocal(pos);
        drawList->AddText({pixelPose.x, pixelPose.y}, col, text.c_str());
    }

    // 绘制坐标

    void DrawArrow(ImDrawList *drawList, const SceneView::Ptr &view, const Pose &pos, const float length, ImU32 col, float thickness)
    {
        Transform pos_tf = PoseToTransform(pos);
        const float arrow_bottom = length * 0.75f;
        const float arrow_width = length * 0.06f;
        Vec2f lineStart = view->FromLocal(pos.pos);
        Vec2f lineEnd = view->FromLocal(Mul(pos_tf, Vec2f(arrow_bottom, 0)));
        Vec2f arrowTop = view->FromLocal(Mul(pos_tf, Vec2f(length, 0)));
        Vec2f arrowLeft = view->FromLocal(Mul(pos_tf, Vec2f(arrow_bottom, arrow_width)));
        Vec2f arrowRight = view->FromLocal(Mul(pos_tf, Vec2f(arrow_bottom, -arrow_width)));
        float pw_thickness = thickness * view->invScale;
        drawList->AddLine({lineStart.x, lineStart.y}, {lineEnd.x, lineEnd.y}, col,
                          pw_thickness);
        drawList->AddTriangleFilled({arrowLeft.x, arrowLeft.y},
                                    {arrowTop.x, arrowTop.y},
                                    {arrowRight.x, arrowRight.y}, col);
    }

    void DrawGrid(ImDrawList *drawList, const SceneManager::Ptr &scene)
    {
        const auto &options = scene->GetOptions();
        CHECK_RETURN(!options->drawGrid);
        auto view = scene->GetSceneView();
        const int grid_width = options->gridWidth;
        const int grid_height = options->gridHeight;
        const float grid_intervel = options->gridInterval;
        const float grid_thickness = options->girdThickness;
        const float grid_dash_size = options->gridDashSize;
        const auto grid_color = options->gridColor;
        const auto grid_x_min = options->gridXmin;
        const auto grid_y_min = options->gridYmin;

        const auto grid_x_max = options->gridXmax;
        const auto grid_y_max = options->gridYmax;
        // 绘制竖向直线

        for (float x = grid_x_min; x <= grid_x_max; x += grid_intervel)
        {
            Vec2f pt_start(x, grid_y_min);
            Vec2f pt_end(x, grid_y_max);
            if ((int(x)) % (5 * (int)grid_intervel) == 0)
            {

                DrawLine(drawList, view, pt_start, pt_end, grid_color, 2.0f * grid_thickness);
                DrawText(drawList, view, {float(x), 0}, grid_color, basis::FormatDoubleValue(x, 2));
            }
            else
            {
                DrawDashedLine(drawList, view, pt_start, pt_end, grid_color, grid_dash_size, grid_thickness);
            }
        }

        for (float y = grid_y_min; y <= grid_y_max; y += grid_intervel)
        {
            Vec2f pt_start(grid_x_min, y);
            Vec2f pt_end(grid_x_max, y);

            if ((int(y)) % (5 * (int)grid_intervel) == 0)
            {

                DrawLine(drawList, view, pt_start, pt_end, grid_color, 2.0f * grid_thickness);
            }
            else
            {
                DrawDashedLine(drawList, view, pt_start, pt_end, grid_color, grid_dash_size, grid_thickness);
            }
            DrawText(drawList, view, {0, float(y)}, grid_color, basis::FormatDoubleValue(y, 2));
        }
    }

    void DrawAxis(ImDrawList *drawList, const SceneView::Ptr &view, const Pose &pos, const float &length, float thickness)
    {
        DrawArrow(drawList, view, pos, length, IM_GREEN, thickness);
        Pose y_axis_pose = pos;
        y_axis_pose.yaw += XVIZ_PI2;
        DrawArrow(drawList, view, y_axis_pose, length, IM_RED, thickness);
    }

    void DrawOriginAxis(ImDrawList *drawList, const SceneManager::Ptr &scene)
    {
        const auto &options = scene->GetOptions();
        CHECK_RETURN(!options->drawOriginAxis);
        auto view = scene->GetSceneView();
        Pose origin_pose;
        origin_pose.pos = {0, 0};
        origin_pose.yaw = 0;
        DrawAxis(drawList, view, origin_pose, options->originAxisLength, options->originAxisThickness);
    }

    void DrawScenePath(ImDrawList *drawList,
                       const SceneView::Ptr &view,
                       const Transform &draw_to_object_tf,
                       unsigned int bk_color,
                       const Path::Ptr &path,
                       float thickness,
                       unsigned int color)
    {

        auto draw_path = Mul(draw_to_object_tf, path->points);
        if (path->isDashed)
        {
            const auto &dash_length = path->dashLength;
            const auto &gap_length = path->gapLength;
            DrawDashedPolyline(drawList, view, draw_path, color, bk_color, thickness, dash_length, gap_length);
        }
        else
        {
            DrawPolyline(drawList, view, draw_path, color, false, thickness);
        }
    }

    void DrawSceneObjects(ImDrawList *drawList, const SceneManager::Ptr &scene)
    {

        const auto options = scene->GetOptions();
        auto view = scene->GetSceneView();
        const auto draw_frame_id = scene->GetDrawFrameID();
        auto tf_tree = scene->GetTFTree();
        auto all_objects_list = scene->GetAllObjects();
        for (auto &scene_objects : *all_objects_list)
        {
            CHECK_CONTINUE(!options->drawObject[scene_objects.first]);
            CHECK_CONTINUE(options->topDrawtype == scene_objects.first);
            CHECK_CONTINUE(scene_objects.second.empty());
            // 获取所有的绘图对象
            std::vector<SceneObject::Ptr> draw_objects;
            scene_objects.second.GatherAll(draw_objects);

            for (auto &draw_object : draw_objects)
            {
                const auto &obj_options = draw_object->GetOptions();
                CHECK_CONTINUE(!obj_options.isVisible);
                CHECK_CONTINUE(!draw_object->HasObject())
                const auto &thickness = obj_options.thickness;
                const auto &color = obj_options.color;
                std::string text_str = draw_object->GetName();
                std::string frame_id = draw_object->GetFrameId();
                auto draw_to_object_tf = tf_tree->LookupTransform(frame_id, draw_frame_id);
                Vec2f text_pose;
                auto bk_color = options->backgroundColor;

                switch (scene_objects.first)
                {
                case SceneObjectType::PATH:
                {
                    // 数据转换
                    ScenePath::Ptr scene_path = std::dynamic_pointer_cast<ScenePath>(std::move(draw_object));
                    const auto &path = scene_path->GetPath();
                    DrawScenePath(drawList, view, draw_to_object_tf, bk_color, path, thickness, color);
                    CHECK_BREAK(path->points.size() == 0);
                    text_pose = Mul(draw_to_object_tf, path->points.front());
                    CHECK_CONTINUE(!obj_options.isShowID);
                    DrawText(drawList, view, text_pose, color, text_str);
                }

                break;
                case SceneObjectType::PATH_ARRAY:
                {
                    // 数据转换
                    ScenePathArray::Ptr scene_path_array = std::dynamic_pointer_cast<ScenePathArray>(std::move(draw_object));
                    const auto &paths = scene_path_array->GetPaths();
                    for (auto &path : paths->paths)
                    {
                        // DrawScenePath(drawList, view, tf_tree, draw_frame_id, options->backgroundColor, path, thickness, color);
                    }
                }
                break;
                case SceneObjectType::POSE:
                {
                    // 数据转换
                    ScenePose::Ptr scene_pose = std::dynamic_pointer_cast<ScenePose>(std::move(draw_object));
                }
                break;
                case SceneObjectType::POSE_ARRAY:
                {
                    // 数据转换
                    ScenePoseArray::Ptr scene_pose_array = std::dynamic_pointer_cast<ScenePoseArray>(std::move(draw_object));
                }
                break;
                case SceneObjectType::POLYGON:
                {
                    // 数据转换
                    ScenePolygon::Ptr scene_polygon = std::dynamic_pointer_cast<ScenePolygon>(std::move(draw_object));
                }
                break;
                case SceneObjectType::POLYGON_ARRAY:
                {
                    // 数据转换
                    ScenePolygonArray::Ptr scene_polygon_array = std::dynamic_pointer_cast<ScenePolygonArray>(std::move(draw_object));
                }
                break;
                case SceneObjectType::CIRCLE:
                {
                    // 数据转换
                    SceneCircle::Ptr scene_circle = std::dynamic_pointer_cast<SceneCircle>(std::move(draw_object));
                }
                break;
                case SceneObjectType::CIRCLE_ARRAY:
                {
                    // 数据转换
                    SceneCircleArray::Ptr scene_circle_array = std::dynamic_pointer_cast<SceneCircleArray>(std::move(draw_object));
                }
                break;
                case SceneObjectType::MARKER:
                {
                    // 数据转换
                    SceneMarker::Ptr scene_marker = std::dynamic_pointer_cast<SceneMarker>(std::move(draw_object));
                }
                break;
                case SceneObjectType::MARKER_ARRAY:
                {
                    // 数据转换
                    SceneMarkerArray::Ptr scene_marker_array = std::dynamic_pointer_cast<SceneMarkerArray>(std::move(draw_object));
                }
                break;
                case SceneObjectType::POINT_CLOUD:
                {
                    // 数据转换
                    ScenePointCloud::Ptr scene_point_cloud = std::dynamic_pointer_cast<ScenePointCloud>(std::move(draw_object));
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    void DrawScene(ImDrawList *drawList, const SceneManager::Ptr &scene)
    {
        // 绘制网格,最底层
        DrawGrid(drawList, scene);
        DrawOriginAxis(drawList, scene);
        // 绘制添加的图形
        DrawSceneObjects(drawList, scene);
    }
}
