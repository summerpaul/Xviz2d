/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 09:48:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-31 16:28:15
 */
#include <stdint.h>

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "scene_objects.h"
#include "basis/transform.h"
#include "basis/xviz_util.h"
#include "rolling_buffer.h"

namespace scene
{
    struct SceneOptions;
    struct SceneView;
    class TFTree;

    class SceneManager
    {
    public:
        typedef std::shared_ptr<SceneManager> Ptr;
        bool Init();
        void AddPath(const std::string &name, const Path *path, const SceneObjectOptions *options = nullptr);
        void AddPathArray(const std::string &name, const PathArray *paths, const SceneObjectOptions *options = nullptr);
        void AddPose(const std::string &name, const Pose *pose, const SceneObjectOptions *options = nullptr);
        void AddPoseArray(const std::string &name, const PoseArray *poses, const SceneObjectOptions *options = nullptr);
        void AddPointCloud(const std::string &name, const PointCloud *point_cloud, const SceneObjectOptions *options = nullptr);
        void AddPolygon(const std::string &name, const Polygon *polygon, const SceneObjectOptions *options = nullptr);
        void AddPolygonArray(const std::string &name, const PolygonArray *polygons, const SceneObjectOptions *options = nullptr);
        void AddCircle(const std::string &name, const Circle *circle, const SceneObjectOptions *options = nullptr);
        void AddCircleArray(const std::string &name, const CircleArray *circles, const SceneObjectOptions *options = nullptr);
        void AddMarker(const std::string &name, const Marker *marker, const SceneObjectOptions *options = nullptr);
        void AddMarkerArray(const std::string &name, const MarkerArray *markers, const SceneObjectOptions *options = nullptr);
        void AddTransformNode(const std::string &name, const TransformNode *tf_node, const SceneObjectOptions *options = nullptr);

        const ScenePoseMap *GetPoseList() const { return &m_poseList; }

        const ScenePathMap *GetPathList() const { return &m_pathList; }
        const ScenePointCloudMap *GetPointCloudList() const { return &m_pointCloudList; }
        const ScenePolygonMap *GetPolygonList() const { return &m_polygonList; }
        const SceneCircleMap *GetCircleList() const { return &m_circleList; }
        const SceneMarkerMap *GetMarkerList() const { return &m_markerList; }
        const SceneTransformNodeMap *GetTransformNodeList() const { return &m_transformNodeList; }
        const SceneMarkerArrayMap *GetMarkerArrayList() const { return &m_markerArrayList; }
        const ScenePathArrayMap *GetPathArrayList() const { return &m_pathArrayList; }
        const ScenePoseArrayMap *GetPoseArrayList() const { return &m_poseArrayList; }
        const ScenePolygonArrayMap *GetPolygonArrayList() const { return &m_polygonArrayList; }
        const SceneCircleArrayMap *GetCircleArrayList() const { return &m_circleArrayList; }
        const SceneAllObjectsMap *GetAllObjects() const { return &m_allSceneObjects; }

        void AddDoubleData(const std::string &name, double x, double y);
        void AddStringData(const std::string &name, const std::string &data);
        void ClearDoubleData();
        const Vec2f &GetMousePose() const { return m_mousePose; }
        void SetMousePose(const Vec2f &pose) { m_mousePose = pose; }
        float GetMousePoseToOriginDist() const { return m_mousePoseToOrigin; }
        void SetMousePoseToOriginDist(float dist) { m_mousePoseToOrigin = dist; }

        const std::shared_ptr<SceneOptions> GetOptions() const { return m_options; }
        const std::shared_ptr<SceneView> GetSceneView() const { return m_view; }
        const std::shared_ptr<TFTree> GetTFTree() const { return m_tfTree; }
        const std::string &GetDrawFrameID() const { return m_drawFrameId; }
        void SetDrawFrameId(const std::string &frame_id) { m_drawFrameId = frame_id; }
        SceneRollingBufferMap &GetDoubleDataList() { return m_doubleDataList; }
        SceneStringMap &GetStringDataList() { return m_stringDataList; }
        const SceneStringMap &GetFrameIdList() const { return m_frameIdList; }

    private:
        std::shared_ptr<SceneOptions> m_options;
        std::shared_ptr<SceneView> m_view;
        std::shared_ptr<TFTree> m_tfTree;

        ScenePoseMap m_poseList;
        ScenePathMap m_pathList;
        ScenePointCloudMap m_pointCloudList;
        ScenePolygonMap m_polygonList;
        SceneCircleMap m_circleList;
        SceneMarkerMap m_markerList;
        SceneTransformNodeMap m_transformNodeList;
        SceneMarkerArrayMap m_markerArrayList;
        ScenePathArrayMap m_pathArrayList;
        ScenePoseArrayMap m_poseArrayList;
        ScenePolygonArrayMap m_polygonArrayList;
        SceneCircleArrayMap m_circleArrayList;
        SceneAllObjectsMap m_allSceneObjects;

        SceneStringMap m_frameIdList;
        SceneRollingBufferMap m_doubleDataList;
        SceneStringMap m_stringDataList;
        std::string m_drawFrameId = WORLD_FRAME;
        Vec2f m_mousePose;
        float m_mousePoseToOrigin = 0.0f;
    };
} // namespace scene

#endif /* __SCENE_MANAGER_H__ */
