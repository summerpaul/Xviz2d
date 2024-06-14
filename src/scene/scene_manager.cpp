/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 15:03:38
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-12 11:16:52
 */
#include <iostream>
#include "scene_manager.h"
#include "scene_options.h"
#include "scene_view.h"
#include "tf_tree.h"
#include "basis/thread_safe_map.h"
using namespace std;

namespace scene
{

    bool SceneManager::Init()
    {
        m_options = std::make_shared<SceneOptions>();
        m_view = std::make_shared<SceneView>();
        m_tfTree = std::make_shared<TFTree>();
        m_tfTree->InsertTransform(WORLD_FRAME, ROOT_FRAME, Transform());
        m_frameIdList[WORLD_FRAME] = WORLD_FRAME;
        return true;
    }

    void SceneManager::AddPath(const std::string &name, const Path *path, const SceneObjectOptions *options)
    {
        if (!m_pathList.Exists(name))
        {
            m_pathList[name] = std::make_shared<ScenePath>();
		
        }
        if (path)
        {
            m_pathList[name]->SetPath(*path);
        }
        if (options)
        {
            m_pathList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::PATH][name] = m_pathList[name];
    }

    void SceneManager::AddPathArray(const std::string &name, const PathArray *paths, const SceneObjectOptions *options)
    {
        if (!m_pathArrayList.Exists(name))
        {
            m_pathArrayList[name] = std::make_shared<ScenePathArray>();
        }
        if (paths)
        {
            m_pathArrayList[name]->SetPaths(*paths);
        }
        if (options)
        {
            m_pathArrayList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::PATH_ARRAY][name] = m_pathArrayList[name];
    }

    void SceneManager::AddPose(const std::string &name, const Pose *pose, const SceneObjectOptions *options)
    {
        if (!m_poseList.Exists(name))
        {
            m_poseList[name] = std::make_shared<ScenePose>();
        }
        if (pose)
        {
            m_poseList[name]->SetPose(*pose);
        }
        if (options)
        {
            m_poseList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::POSE][name] = m_poseList[name];
    }

    void SceneManager::AddPoseArray(const std::string &name, const PoseArray *poses, const SceneObjectOptions *options)
    {
        if (!m_poseArrayList.Exists(name))
        {
            m_poseArrayList[name] = std::make_shared<ScenePoseArray>();
        }
        if (poses)
        {
            m_poseArrayList[name]->SetPoses(*poses);
        }
        if (options)
        {
            m_poseArrayList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::POSE_ARRAY][name] = m_poseArrayList[name];
    }

    void SceneManager::AddPointCloud(const std::string &name, const PointCloud *point_cloud, const SceneObjectOptions *options)
    {
        if (!m_pointCloudList.Exists(name))
        {
            m_pointCloudList[name] = std::make_shared<ScenePointCloud>();
        }
        if (point_cloud)
        {
            m_pointCloudList[name]->SetPointCloud(*point_cloud);
        }
        if (options)
        {
            m_pointCloudList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::POINT_CLOUD][name] = m_pointCloudList[name];
    }

    void SceneManager::AddPolygon(const std::string &name, const Polygon *polygon, const SceneObjectOptions *options)
    {
        if (!m_polygonList.Exists(name))
        {
            m_polygonList[name] = std::make_shared<ScenePolygon>();
        }
        if (polygon)
        {
            m_polygonList[name]->SetPolygon(*polygon);
        }
        if (options)
        {
            m_polygonList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::POLYGON][name] = m_polygonList[name];
    }

    void SceneManager::AddPolygonArray(const std::string &name, const PolygonArray *polygons, const SceneObjectOptions *options)
    {
        if (!m_polygonArrayList.Exists(name))
        {
            m_polygonArrayList[name] = std::make_shared<ScenePolygonArray>();
        }
        if (polygons)
        {
            m_polygonArrayList[name]->SetPolygons(*polygons);
        }
        if (options)
        {
            m_polygonArrayList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::POLYGON_ARRAY][name] = m_polygonArrayList[name];
    }

    void SceneManager::AddCircle(const std::string &name, const Circle *circle, const SceneObjectOptions *options)
    {
        if (!m_circleList.Exists(name))
        {
            m_circleList[name] = std::make_shared<SceneCircle>();
        }
        if (circle)
        {
            m_circleList[name]->SetCircle(*circle);
        }
        if (options)
        {
            m_circleList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::CIRCLE][name] = m_circleList[name];
    }

    void SceneManager::AddCircleArray(const std::string &name, const CircleArray *circles, const SceneObjectOptions *options)
    {
        if (!m_circleArrayList.Exists(name))
        {
            m_circleArrayList[name] = std::make_shared<SceneCircleArray>();
        }
        if (circles)
        {
            m_circleArrayList[name]->SetCircles(*circles);
        }
        if (options)
        {
            m_circleArrayList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::CIRCLE_ARRAY][name] = m_circleArrayList[name];
    }

    void SceneManager::AddMarker(const std::string &name, const Marker *marker, const SceneObjectOptions *options)
    {
        if (!m_markerList.Exists(name))
        {
            m_markerList[name] = std::make_shared<SceneMarker>();
        }
        if (marker)
        {
            m_markerList[name]->SetMarker(*marker);
        }
        if (options)
        {
            m_markerList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::MARKER][name] = m_markerList[name];
    }

    void SceneManager::AddMarkerArray(const std::string &name, const MarkerArray *markers, const SceneObjectOptions *options)
    {
        if (!m_markerArrayList.Exists(name))
        {
            m_markerArrayList[name] = std::make_shared<SceneMarkerArray>();
        }
        if (markers)
        {
            m_markerArrayList[name]->SetMarkers(*markers);
        }
        if (options)
        {
            m_markerArrayList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::MARKER_ARRAY][name] = m_markerArrayList[name];
    }

    void SceneManager::AddTransformNode(const std::string &name, const TransformNode *tf_node, const SceneObjectOptions *options)
    {
        if (!m_transformNodeList.Exists(name))
        {
            m_transformNodeList[name] = std::make_shared<SceneTransformNode>();
        }
        if (tf_node)
        {
            m_transformNodeList[name]->SetTransformNode(*tf_node);
        }
        if (options)
        {
            m_transformNodeList[name]->SetOptions(*options);
        }
        m_allSceneObjects[SceneObjectType::TRANSFORM_NODE][name] = m_transformNodeList[name];
        Transform tf(tf_node->trans, tf_node->yaw);
        m_tfTree->InsertTransform(name, tf_node->parentFrameId, tf);
        m_frameIdList[name] = name;
    }

    void SceneManager::AddDoubleData(const std::string &name, double x, double y)
    {
        auto RandomColor = []()
        {
            ImVec4 col;
            col.x = RandomRange(0.0f, 1.0f);
            col.y = RandomRange(0.0f, 1.0f);
            col.z = RandomRange(0.0f, 1.0f);
            col.w = 1.0f;
            return col;
        };

        if (!m_doubleDataList.Exists(name))
        {
            m_doubleDataList[name].color = RandomColor();
            m_doubleDataList[name].isPlt = false;
            m_doubleDataList[name].yax = 3;
        }
        m_doubleDataList[name].AddPoint(x, y);
    }
    void SceneManager::AddStringData(const std::string &name, const std::string &data)
    {
        m_stringDataList[name] = data;
    }
    void SceneManager::ClearDoubleData()
    {
        m_doubleDataList.RemoveAll();
    }
}