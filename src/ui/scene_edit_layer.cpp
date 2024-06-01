/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-27 11:43:32
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-01 10:04:35
 */
#include <iostream>

#include "scene_edit_layer.h"
#include "app/app.h"
#include "basis/logger.h"
#include "scene/scene_manager.h"
#include "scene/scene_options.h"
#include "scene/scene_view.h"

namespace ui
{

    void ScenebjectOptionsEdit(const std::string &name,
                               scene::SceneObjectOptions &options,
                               bool useThickness,
                               bool useLength,
                               bool useRadius,
                               bool useColor)
    {
        if (ImGui::TreeNode(name.data()))
        {
            // int configNum = 0;
            if (useThickness)
            {
                ImGui::Text("thickness");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::SliderFloat(("##" + name + "thickness").data(),
                                   &options.thickness, 0.01f, 0.5f,
                                   "%.2f m");
                // configNum++;
            }

            if (useLength)
            {
                ImGui::Text("length");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::SliderFloat(("##" + name + " length").data(), &options.length,
                                   0.5f, 10.0f, "%.2f m");
            }

            if (useRadius)
            {

                ImGui::Text("radius");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::SliderFloat(("##" + name + " radius").data(), &options.radius,
                                   0.01f, 0.5f, "%.2f m");
            }
            if (useColor)
            {

                ImColor color(options.color);
                ImGui::Text("color");
                ImGui::SameLine();
                ImGui::ColorEdit4(("##" + name + " color").data(), (float *)&color,
                                  ImGuiColorEditFlags_NoInputs |
                                      ImGuiColorEditFlags_NoLabel);
                options.color = color;
            }

            ImGui::Text("Visible ");
            ImGui::SameLine();
            ImGui::Checkbox(("##" + name + " Visible").data(), &options.isVisible);

            ImGui::Text("ShowId ");
            ImGui::SameLine();
            ImGui::Checkbox(("##" + name + " ShowId").data(), &options.isShowID);
            ImGui::TreePop();
        }
    }

    SceneEditLayer::SceneEditLayer(const std::string &name) : BaseLayer(name)
    {
    }
    void SceneEditLayer::Draw()
    {
        ImGui::Begin(m_name.data());

        StyleEdit();
        auto options = m_scene->GetOptions();
        SceneEdit(options);
        SceneViewEdit(options);
        SceneObjectsEdit(options);

        PlotUiContextEdit();

        ImGui::End();
    }
    bool SceneEditLayer::Init()
    {
        m_scene = app::App::GetInstance()->GetSceneManager();
        if (!m_scene)
        {
            LOG_ERROR("SceneEditLayer is not initialized");

            return false;
        }
        LOG_INFO("SceneEditLayer Init");
        m_initialized = true;

        return true;
    }

    void SceneEditLayer::Shutdown()
    {
    }

    void SceneEditLayer::SetUIContext(const UIContext::Ptr &ui_context)
    {
        m_uiContext = ui_context;
    }

    void SceneEditLayer::SceneEdit(std::shared_ptr<scene::SceneOptions> &options)
    {

        if (ImGui::TreeNode("SceneEdit:"))
        {

            ImGui::Text("Background");
            ImGui::SameLine();
            ImColor backgroundColor(options->backgroundColor);
            ImGui::ColorEdit4("##Background", (float *)&backgroundColor,
                              ImGuiColorEditFlags_NoInputs);
            options->backgroundColor = backgroundColor;

            SceneGridEdit(options);
            SceneOriginAxisEdit(options);

            ImGui::TreePop();
        }
    }

    void SceneEditLayer::SceneGridEdit(std::shared_ptr<scene::SceneOptions> &options)
    {

        if (ImGui::TreeNode("Grid"))
        {
            ImGui::Text("Visable");
            ImGui::SameLine();
            ImGui::Checkbox("##DrawGrid", &(options->drawGrid));

            ImGui::Text("Color");
            ImGui::SameLine();
            ImColor gridColor(options->gridColor);
            ImGui::ColorEdit4("##GridColor", (float *)&gridColor,
                              ImGuiColorEditFlags_NoInputs);
            options->gridColor = gridColor;

            ImGui::Text("Width");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderInt("##GridWidth", &options->gridWidth, 1, 50);

            ImGui::Text("Height");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderInt("##GridHeight", &options->gridHeight, 1,
                             50);

            ImGui::Text("Interval");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("##GridInterval", &options->gridInterval, 0.5f,
                               4.0f, "%.1f m");

            ImGui::Text("DashSize");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("##GridDashSize", &options->gridDashSize, 0.05f,
                               0.5f, "%.2f m");

            ImGui::Text("Thickness");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("##GridThickness", &options->girdThickness,
                               0.01f, 0.2f, "%.2f");

            ImGui::TreePop();
        }
    }
    void SceneEditLayer::SceneOriginAxisEdit(std::shared_ptr<scene::SceneOptions> &options)
    {
        if (ImGui::TreeNode("OriginAxisEdit"))
        {

            ImGui::Text("Visable");
            ImGui::SameLine();
            ImGui::Checkbox("##DrawOriginAxis", &(options->drawOriginAxis));

            ImGui::Text("Length");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("##AxisLength", &options->originAxisLength, 1.0f,
                               10.0f, "%.1f m");

            ImGui::TreePop();
        }
    }
    void SceneEditLayer::SceneViewEdit(std::shared_ptr<scene::SceneOptions> &options)
    {

        if (ImGui::TreeNode("ViewEdit"))
        {
            auto view = m_scene->GetSceneView();
            const float &minZoom = options->minZoom;
            const float &maxZoom = options->maxZoom;

            ImGui::Text("ViewScale:");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            if (ImGui::SliderFloat("##ViewScale", &view->scale, minZoom,
                                   maxZoom, "%.3f"))
            {
                view->SetScale(view->scale);
            }

            ImGui::Text("Origin X:");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::InputFloat("##Origin x", &view->origin.x, 0, 0, "%.2f m");

            ImGui::Text("Origin Y:");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::InputFloat("##Origin y", &view->origin.y, 0, 0, "%.2f m");

            ImGui::TreePop();
        }
    }

    void SceneEditLayer::SceneObjectsEdit(std::shared_ptr<scene::SceneOptions> &options)
    {

        if (ImGui::TreeNode("SceneObjects"))
        {
            auto all_objects = m_scene->GetAllObjects();
            for (auto &object : *all_objects)
            {
                auto type = object.first;

                std::vector<scene::SceneObject::Ptr> draw_objects;
                object.second.GatherAll(draw_objects);
                CHECK_CONTINUE(draw_objects.size() == 0);

                if (ImGui::TreeNode(scene::SceneObjectStr[type].data()))
                {
                    ImGui::Text("Visable");
                    ImGui::SameLine();
                    ImGui::Checkbox(("##" + scene::SceneObjectStr[type] + "vis").data(), &options->drawObject[type]);
                    for (auto &draw_object : draw_objects)
                    {
                        auto name = draw_object->GetName();

                        ScenebjectOptionsEdit(name, draw_object->GetOptions(), true, true, true, true);
                    }

                    ImGui::TreePop();
                };
            }

            ImGui::TreePop();
        }
    }

    void SceneEditLayer::PlotUiContextEdit()
    {
        auto &lims = m_uiContext->lims;
        if (ImGui::TreeNode("PlotUIEdit"))
        {
            ImGui::SetNextItemWidth(150);
            ImGui::SliderInt("Rows", &m_uiContext->rows, 1, 5);
            ImGui::SetNextItemWidth(150);
            ImGui::SliderInt("Cols", &m_uiContext->cols, 1, 5);
            ImGui::SetNextItemWidth(150);
            ImGui::DragScalarN("Row Ratios", ImGuiDataType_Float, m_uiContext->rratios, m_uiContext->rows, 0.01f, nullptr);
            ImGui::SetNextItemWidth(150);
            ImGui::DragScalarN("Col Ratios", ImGuiDataType_Float, m_uiContext->cratios, m_uiContext->cols, 0.01f, nullptr);
            ImGui::SetNextItemWidth(150);
            ImGui::DragScalarN("Limits", ImGuiDataType_Double, &lims.X.Min, 4, 0.01f);
            ImGui::SetNextItemWidth(150);
            ImGui::Checkbox("X Axis Links", &m_uiContext->linkx);
            ImGui::TreePop();
        }
    }
    void SceneEditLayer::StyleEdit()
    {
        if (ImGui::TreeNode("StyleEdit"))
        {
            ImGui::SetNextItemWidth(100);
            ImGui::ShowStyleSelector("ImGui Style");
            ImGui::SetNextItemWidth(100);
            ImPlot::ShowStyleSelector("ImPlot Style");
            ImGui::SetNextItemWidth(100);
            ImPlot::ShowColormapSelector("ImPlot Colormap");
            ImGui::SetNextItemWidth(100);
            ImPlot::ShowInputMapSelector("Input Map");
            ImGui::SetNextItemWidth(100);
            ImGui::TreePop();
        }
    }

} // namespace ui
