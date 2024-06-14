/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:00:52
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-12 11:16:57
 */
#include <iostream>

#include "app/app.h"
#include "basis/logger.h"
#include "basis/transform.h"
#include "basis/xviz_util.h"
#include "scene/scene_draw.h"
#include "scene/scene_manager.h"
#include "scene/scene_options.h"
#include "scene/scene_view.h"
#include "scene/tf_tree.h"
#include "scene_layer.h"

using namespace basis;
namespace ui {
SceneLayer::SceneLayer(const std::string &name) : BaseLayer(name) {}

bool SceneLayer::Init() {

  m_scene = app::App::GetInstance()->GetSceneManager();
  if (!m_scene) {
    LOG_ERROR("SceneLayer is not initialized");

    return false;
  }
  LOG_INFO("SceneLayer Init");
  m_initialized = true;
  return true;
}

void SceneLayer::Draw() {

  ImGui::Begin(m_name.data());
  auto view = m_scene->GetSceneView();
  view->SetPosition({ImGui::GetWindowPos().x, ImGui::GetWindowPos().y});
  view->SetSize({ImGui::GetWindowSize().x, ImGui::GetWindowSize().y});
  ImVec2 view_rect_min{view->GetViewRectMin().x, view->GetViewRectMin().y};
  ImVec2 view_rect_max{view->GetViewRectMax().x, view->GetViewRectMax().y};
  auto options = m_scene->GetOptions();
  ImDrawList *drawList = ImGui::GetWindowDrawList();
  drawList->AddRectFilled(view_rect_min, view_rect_max,
                          options->backgroundColor);
  DrawScene(drawList, m_scene);
  HandleMouse();
  ImGui::End();
}

void SceneLayer::Shutdown() {}

void SceneLayer::SetUIContext(const UIContext::Ptr &ui_context) {
  m_uiContext = ui_context;
}

void SceneLayer::HandleMouse() {

  ImGuiIO &io = ImGui::GetIO();
  ImGui::InvisibleButton("SceneLayer", ImGui::GetWindowSize(),
                         ImGuiButtonFlags_MouseButtonLeft |
                             ImGuiButtonFlags_MouseButtonRight);
  if (ImGui::IsItemHovered()) {
    HandleZoomScroll(io);
    HandleMeasure(io);
  }
  HandleMouseMenu();
}

void SceneLayer::HandleZoomScroll(const ImGuiIO &io) {
  auto options = m_scene->GetOptions();
  auto view = m_scene->GetSceneView();
  Vec2f mousePosePixel{io.MousePos.x, io.MousePos.y};
  Vec2f mousePositionScene = view->ToLocal(mousePosePixel);
  m_scene->SetMousePose(mousePositionScene);
  m_scene->SetMousePoseToOriginDist(Length(mousePositionScene));
  auto tf_tree = m_scene->GetTFTree();
  const auto &draw_frame_id = m_scene->GetDrawFrameID();
  if (tf_tree->CanTransform(draw_frame_id, WORLD_FRAME)) {
    auto tf = tf_tree->LookupTransform(draw_frame_id, WORLD_FRAME);
    m_scene->SetMousePose(Mul(tf, mousePositionScene));
  }
  const float zoomStep = options->zoomStep;
  const float minZoom = options->minZoom;
  const float maxZoom = options->maxZoom;
  const float deltaZoom = Sign(io.MouseWheel) * zoomStep;
  const Vec2f origin = view->origin;
  const float scalePre = view->scale;
  const float invScalePre = view->invScale;
  Vec2f targetOrigin =
      origin - deltaZoom * invScalePre * (mousePositionScene - origin);
  float targetScale = scalePre + deltaZoom;
  if (targetScale >= minZoom && targetScale <= maxZoom) {
    view->SetScale(targetScale);
    view->SetOrigin(targetOrigin);
  }

  static bool lastRightBtnDown = false;
  static Vec2f mousePosePre;
  static Vec2f originPre;
  if (io.MouseDown[1]) {
    if (!lastRightBtnDown) {
      mousePosePre = mousePosePixel;
      originPre = view->origin;
      lastRightBtnDown = true;
    } else {
      ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
      view->DragScene(mousePosePre, mousePosePixel, originPre);
    }
  }

  if (io.MouseReleased[1]) {

    lastRightBtnDown = false;
  }
}

void SceneLayer::HandleMouseMenu() {

  ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);

  if (drag_delta.x == 0.0f && drag_delta.y == 0.0f) {
    ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
  }

  if (ImGui::BeginPopup("context")) {
    auto options = m_scene->GetOptions();
    auto view = m_scene->GetSceneView();
    if (ImGui::MenuItem("Clear")) {
      // m_scene->Clear();
    }

    if (ImGui::MenuItem("Clear All")) {
      // scene->ClearAll();
    }

    ImGui::Checkbox("DrawMeasure", &options->drawMeasure);

    ImGui::Text("Color");
    ImGui::SameLine();
    ImColor measureColor(options->measureColor);
    ImGui::ColorEdit4("##MeasureColor", (float *)&measureColor,
                      ImGuiColorEditFlags_NoInputs);
    options->measureColor = measureColor;

    ImGui::Checkbox("DrawOriginAxis", &options->drawOriginAxis);

    ImGui::Checkbox("DrawGrid", &options->drawGrid);
    ImGui::Checkbox("Draw tf", &options->drawTransformNodeList);
    ImGui::Text("FrameId");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    if (ImGui::BeginCombo("##DrawFrameID", m_scene->GetDrawFrameID().data(),
                          ImGuiComboFlags_NoArrowButton)) {
      for (auto &frameId : m_scene->GetFrameIdList()) {
        bool is_selected = frameId.second == m_scene->GetDrawFrameID();
        if (ImGui::Selectable(frameId.second.data(), is_selected)) {
          m_scene->SetDrawFrameId(frameId.second);
        }

        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }

    ImGui::Text("TopObject");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150);
    if (ImGui::BeginCombo("##TopDrawObject", options->topDrawtypeStr.data(),
                          ImGuiComboFlags_NoArrowButton)) {
      for (int i = 0; i < scene::SceneObjectType::OBJECT_NUM; i++) {
        auto objectTypeStr = scene::SceneObjectStr[i];
        bool is_selected = objectTypeStr == options->topDrawtypeStr;

        if (ImGui::Selectable(objectTypeStr.data(), is_selected)) {
          options->topDrawtype = i;
          options->topDrawtypeStr = objectTypeStr;
        }

        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }

    ImGui::Text("BottomObject");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150);
    if (ImGui::BeginCombo("##BottomDrawObject", options->bottomDrawtypeStr.data(),
                          ImGuiComboFlags_NoArrowButton)) {
      for (int i = 0; i < scene::SceneObjectType::OBJECT_NUM; i++) {
        auto objectTypeStr = scene::SceneObjectStr[i];
        bool is_selected = objectTypeStr == options->bottomDrawtypeStr;

        if (ImGui::Selectable(objectTypeStr.data(), is_selected)) {
          options->bottomDrawtype = i;
          options->bottomDrawtypeStr = objectTypeStr;
        }

        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }

    if (ImGui::MenuItem("OriginToCenter")) {
      view->OriginToCenter();
    }

    ImGui::Text("Move To:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    static std::string target_frame_id = m_scene->GetDrawFrameID();
    if (ImGui::BeginCombo("##MoveTo", target_frame_id.data(),
                          ImGuiComboFlags_NoArrowButton)) {
      for (auto &frameId : m_scene->GetFrameIdList()) {
        bool is_selected = frameId.second == m_scene->GetDrawFrameID();

        if (ImGui::Selectable(frameId.second.data(), is_selected)) {
          target_frame_id = frameId.second;
          auto tf_tree = m_scene->GetTFTree();
          if (tf_tree->CanTransform(m_scene->GetDrawFrameID(),
                                    frameId.second)) {
            auto tf = tf_tree->LookupTransform(frameId.second,
                                               m_scene->GetDrawFrameID());
            const auto size = view->scale * view->size;

            view->SetOrigin(1.0f * tf.trans - 0.5 * size);
          }
        }

        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }

    ImGui::EndPopup();
  }
}

void SceneLayer::HandleMeasure(const ImGuiIO &io) {
  auto options = m_scene->GetOptions();
  auto view = m_scene->GetSceneView();
  CHECK_RETURN(!options->drawMeasure);
  ImDrawList *drawList = ImGui::GetWindowDrawList();
  static bool lastLeftBtnDown = false;
  static ImVec2 start_pose;
  static ImVec2 end_pose;
  if (io.MouseDown[0]) {
    if (!lastLeftBtnDown) {
      lastLeftBtnDown = true;
      start_pose = io.MousePos;
    } else {
      end_pose = io.MousePos;
      drawList->AddLine(start_pose, end_pose, options->measureColor, 2.0f);
      Vec2f start{start_pose.x, start_pose.y};
      Vec2f end{end_pose.x, end_pose.y};
      const float dist = Distance(start, end) * view->scale;
      ImVec2 text_pose;
      text_pose.x = 0.5f * (start_pose.x + end_pose.x);
      text_pose.y = 0.5f * (start_pose.y + end_pose.y);
      drawList->AddText(text_pose, options->measureColor,
                        (FormatFloatValue(dist, 2) + " m").data());
    }
  }

  if (io.MouseReleased[0]) {
    lastLeftBtnDown = false;
  }
}

} // namespace ui
