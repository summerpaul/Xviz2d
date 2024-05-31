/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:02:34
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 14:10:11
 */
#include "plot_layer.h"
#include "app/app.h"
#include "scene/scene_manager.h"

#include <implot.h>
#include "basis/logger.h"
#include <algorithm>
#include <vector>

#include <imgui_internal.h>

int GetBinarySearchIndex(const std::vector<double> &sortedArray, const double &targetValue)
{
    int id = -1;
    auto lower = std::lower_bound(sortedArray.begin(), sortedArray.end(), targetValue);
    if (lower == sortedArray.end())
    {
        id = -1;
    }
    else
    {
        id = int(std::distance(sortedArray.begin(), lower) - 1);
    }
    return id;
}

namespace ui
{

    PlotLayer::PlotLayer(const std::string &name)
        : BaseLayer(name)
    {
    }
    void PlotLayer::Draw()
    {
        ImGui::Begin(m_name.data());
        DrawTable();
        ImGui::SameLine();
        DrawCharts(m_name.data());
        ImGui::End();
    }
    bool PlotLayer::Init()
    {
        m_scene = app::App::GetInstance()->GetSceneManager();
        CHECK_RETURN_RET(!m_scene, false);
        ImPlot::CreateContext();
        ImPlot::StyleColorsLight();
        LOG_INFO("SceneManager  initialized");
        m_initialized = true;
        return true;
    }

    void PlotLayer::Shutdown()
    {
        ImPlot::DestroyContext();
        LOG_INFO("Shutdown");
    }

    void PlotLayer::SetUIContext(const UIContext::Ptr &ui_context)
    {
        m_uiContext = ui_context;
    }

    void PlotLayer::DrawTable()
    {

        static ImGuiTableFlags table_flags =
            ImGuiTableFlags_Borders | ImGuiTableFlags_BordersV |
            ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable |
            ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter;

        auto &draw_datas = m_scene->GetDoubleDataList();
        const auto &isShowDragX1 = m_uiContext->isShowDragX1;
        const auto &isShowDragX2 = m_uiContext->isShowDragX2;
        const auto &string_datas = m_scene->GetStringDataList();
        int col_num = 2;
        if (isShowDragX1)
        {
            col_num += 1;
        }
        if (isShowDragX2)
        {
            col_num += 1;
        }
        if (isShowDragX1 && isShowDragX2)
        {
            col_num += 1;
        }
        ImGui::BeginChild("DND_LEFT", ImVec2(400, -1));

        if (ImGui::BeginTable("TableView", col_num, table_flags))
        {
            ImGui::TableSetupColumn("name");
            ImGui::TableSetupColumn("Value");
            if (isShowDragX1)
            {
                ImGui::TableSetupColumn("Value1");
            }
            if (isShowDragX2)
            {
                ImGui::TableSetupColumn("Value2");
            }
            if (isShowDragX1 && isShowDragX2)
            {
                ImGui::TableSetupColumn("DeltaValue");
            }
            ImGui::TableHeadersRow();
            for (auto &data : draw_datas)
            {
                DrawSelectedData(data.first.data(), data.second);
            }
            for (auto &data : draw_datas)
            {
                DrawUnselectedData(data.first.data(), data.second);
            }

            for (auto &data : string_datas)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Selectable(data.first.data(), false, 0, ImVec2(150, 0));
                ImGui::TableSetColumnIndex(1);
                ImGui::Selectable(data.second.data(), false, 0, ImVec2(150, 0));
            }

            ImGui::EndTable();
        }

        if (ImGui::BeginDragDropTarget())
        {

            auto *payload = ImGui::AcceptDragDropPayload("MY_DND");
            if (payload)
            {
                const char *name = (const char *)payload->Data;
                draw_datas[name].isPlt = false;
            }

            ImGui::EndDragDropTarget();
        }

        ImGui::EndChild();
    }

    void PlotLayer::DrawSelectedData(const char *title, const RollingBuffer &data)
    {
        const auto &isShowDragX1 = m_uiContext->isShowDragX1;
        const auto &isShowDragX2 = m_uiContext->isShowDragX2;
        const auto &idx1 = m_uiContext->idx1;
        const auto &idx2 = m_uiContext->idx2;
        CHECK_RETURN(data.xs.empty() || data.ys.empty() || data.xs.size() != data.ys.size());
        CHECK_RETURN(!data.isPlt);
        CHECK_RETURN(idx1 >= data.xs.size() || idx2 >= data.xs.size());

        int col_index = 0;
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(col_index++);
        ImGui::Selectable(title, true, 0, ImVec2(150, 0));
        ImGui::TableSetColumnIndex(col_index++);
        const auto &cur_value = data.ys.back();
        ImGui::Selectable(FormatDoubleValue(cur_value, 2).data(), true, 0,
                          ImVec2(150, 0));
        double val1 = 0;
        double val2 = 0;
        if (isShowDragX1 && idx1 >= 0)
        {
            ImGui::TableSetColumnIndex(col_index++);
            val1 = data.ys[idx1];
            ImGui::Selectable(FormatDoubleValue(val1, 2).data(), true, 0,
                              ImVec2(150, 0));
        }
        if (isShowDragX2 && idx2 >= 0)
        {
            ImGui::TableSetColumnIndex(col_index++);
            val2 = data.ys[idx2];
            ImGui::Selectable(FormatDoubleValue(val2, 2).data(), true, 0,
                              ImVec2(150, 0));
        }
        if (isShowDragX1 && isShowDragX2)
        {
            ImGui::TableSetColumnIndex(col_index++);
            auto delta = val2 - val1;
            ImGui::Selectable(FormatDoubleValue(delta, 2).data(), true, 0,
                              ImVec2(150, 0));
        }
    }
    
    void PlotLayer::DrawUnselectedData(const std::string &title, const RollingBuffer &data)
    {

        const auto &isShowDragX1 = m_uiContext->isShowDragX1;
        const auto &isShowDragX2 = m_uiContext->isShowDragX2;
        const auto &idx1 = m_uiContext->idx1;
        const auto &idx2 = m_uiContext->idx2;
        CHECK_RETURN(data.xs.empty() || data.ys.empty() || data.xs.size() != data.ys.size());
        CHECK_RETURN(data.isPlt);
        int col_index = 0;
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(col_index++);
        ImGui::Selectable(title.data(), false, 0, ImVec2(150, 0));
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
            ImGui::SetDragDropPayload("MY_DND", title.data(),
                                      title.size() * sizeof(title[0]));
            ImPlot::ItemIcon(data.color);
            ImGui::SameLine();
            ImGui::TextUnformatted(title.data());
            ImGui::EndDragDropSource();
        }
        ImGui::TableSetColumnIndex(col_index++);
        const auto &cur_value = data.ys.back();
        ImGui::Selectable(FormatDoubleValue(cur_value, 2).data(), false, 0,
                          ImVec2(100, 0));
        double val1 = 0;
        double val2 = 0;
        if (isShowDragX1 && idx1 >= 0)
        {
            ImGui::TableSetColumnIndex(col_index++);
            val1 = data.ys[idx1];
            ImGui::Selectable(FormatDoubleValue(val1, 2).data(), false, 0,
                              ImVec2(100, 0));
        }
        if (isShowDragX2 && idx2 >= 0)
        {
            ImGui::TableSetColumnIndex(col_index++);
            val2 = data.ys[idx2];
            ImGui::Selectable(FormatDoubleValue(val2, 2).data(), false, 0,
                              ImVec2(100, 0));
        }
        if (isShowDragX1 && isShowDragX2)
        {
            ImGui::TableSetColumnIndex(col_index++);
            auto delta = val2 - val1;
            ImGui::Selectable(FormatDoubleValue(delta, 2).data(), false, 0,
                              ImVec2(100, 0));
        }
    }

    void PlotLayer::DrawCharts(const char *title)
    {
        const int &rows = m_uiContext->rows;
        const int &cols = m_uiContext->cols;
        auto &rratios = m_uiContext->rratios;
        auto &cratios = m_uiContext->cratios;
        auto &lims = m_uiContext->lims;
        auto dragX1Color = &m_uiContext->dragX1Color.x;
        auto dragX2Color = &m_uiContext->dragX2Color.x;
        auto dragX1 = &m_uiContext->dragX1;
        auto dragX2 = &m_uiContext->dragX2;
        auto isShowDragX1 = &m_uiContext->isShowDragX1;
        auto isShowDragX2 = &m_uiContext->isShowDragX2;
        static ImPlotSubplotFlags flags = ImPlotSubplotFlags_NoTitle;
        auto &draw_datas = m_scene->GetDoubleDataList();
        ImGui::BeginChild("DND_RIGHT", ImVec2(-1, -1));

        DrawDragBar("X1", lims.X.Min, lims.X.Max, dragX1, dragX1Color, isShowDragX1);
        ImGui::SameLine();
        if (ImGui::Button("Clear"))
        {
            for (auto &data : draw_datas)
            {
                data.second.Erase();
            }
        }

        DrawDragBar("X2", lims.X.Min, lims.X.Max, dragX2, dragX2Color, isShowDragX2);
        ImGui::SameLine();
        ImGui::Checkbox("AutoFit", &m_uiContext->autoFit);
        if (ImPlot::BeginSubplots("DataPlot", rows, cols, ImVec2(-1, -1), flags, rratios, cratios))
        {
            for (int i = 0; i < rows * cols; ++i)
            {

                DrawSingleChart(("xvix_chart" + std::to_string(i)).data());
            }

            ImPlot::EndSubplots();
        }

        ImGui::EndChild();
    }

    void PlotLayer::DrawSingleChart(const char *title)
    {
        static ImPlotFlags flags = ImPlotSubplotFlags_NoTitle | ImPlotFlags_Crosshairs;
        auto &lims = m_uiContext->lims;
        const bool &linkx = m_uiContext->linkx;
        auto &drag_value1 = m_uiContext->dragX1;
        auto &drag_value2 = m_uiContext->dragX2;
        auto &drag_color1 = m_uiContext->dragX1Color;
        auto &drag_color2 = m_uiContext->dragX2Color;
        auto &plotDataList = m_scene->GetDoubleDataList();
        auto &drag_x1 = m_uiContext->dragX1;
        auto &drag_x2 = m_uiContext->dragX2;
        auto &last_drag_x1 = m_uiContext->lastDragX1;
        auto &last_drag_x2 = m_uiContext->lastDragX2;
        auto &idx1 = m_uiContext->idx1;
        auto &idx2 = m_uiContext->idx2;
        const bool isShowDragX1 = m_uiContext->isShowDragX1;
        const bool isShowDragX2 = m_uiContext->isShowDragX2;

        if (ImPlot::BeginPlot(title, ImVec2(), flags))
        {

            SetUpPlotAxis();
            ImPlot::SetupAxisLinks(ImAxis_X1, linkx ? &lims.X.Min : nullptr, linkx ? &lims.X.Max : nullptr);
            ImPlot::SetupLegend(ImPlotLocation_North | ImPlotLocation_West, ImPlotLegendFlags_Horizontal | ImPlotLegendFlags_Sort);
            if (isShowDragX1)
            {
                DrawDragLineTagX("X1", &drag_value1, drag_color1, 1, lims.X.Min, lims.X.Max);
            }
            if (isShowDragX2)
            {
                DrawDragLineTagX("X2", &drag_value2, drag_color2, 2, lims.X.Min, lims.X.Max);
            }

            if (!plotDataList.empty() && drag_x1 != last_drag_x1)
            {
                idx1 = GetBinarySearchIndex(plotDataList.begin()->second.xs, drag_x1);
                last_drag_x1 = drag_x1;
            }

            if (!plotDataList.empty() && drag_x2 != last_drag_x2)
            {
                idx2 = GetBinarySearchIndex(plotDataList.begin()->second.xs, drag_x2);
                last_drag_x2 = drag_x2;
            }

            for (auto &plotData : plotDataList)
            {
                DrawSinglePlotData(title, plotData.first, plotData.second);
            }
            if (ImPlot::IsPlotHovered())
            {
                DrawTooltips();
            }
            SetPlotDragDropTarget(title);

            ImPlot::EndPlot();
        }
    }
    void PlotLayer::DrawSinglePlotData(const std::string &title, const std::string &data_name, RollingBuffer &plotData)
    {
        const size_t data_size = plotData.xs.size();
        CHECK_RETURN(data_size <= 0);
        CHECK_RETURN(!plotData.isPlt);
        CHECK_RETURN(title != plotData.plotChartName);
        ImPlot::SetAxis(plotData.yax);
        ImPlot::SetNextLineStyle(plotData.color, plotData.thickness);
        if (ImPlot::BeginLegendPopup(data_name.data()))
        {

            ImGui::Text("Color");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::ColorEdit4((data_name + "-color").data(), &plotData.color.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
            ImGui::Separator();
            ImGui::Text("Thickness");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(100);
            ImGui::SliderFloat(("##" + data_name + "Thickness").data(), &plotData.thickness, 0.1f, 3.0f);
            ImGui::Separator();
            ImGui::Text("isStair");
            ImGui::SameLine();
            ImGui::Checkbox(("##" + data_name + "isStair").data(), &plotData.isStair);
            ImGui::Separator();
            ImGui::Text("isMarkers");
            ImGui::SameLine();
            ImGui::Checkbox(("##" + data_name + "isMarkers").data(), &plotData.isMarkers);

            ImPlot::EndLegendPopup();
        }
        if (plotData.isMarkers)
        {
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        }
        if (!plotData.isStair)
        {

            ImPlot::PlotLine(data_name.data(), &plotData.xs[0], &plotData.ys[0], int(data_size));
        }
        else
        {
            ImPlot::PlotStairs((data_name).data(), &plotData.xs[0], &plotData.ys[0], int(data_size));
        }

        if (ImPlot::IsPlotHovered() && ImGui::GetIO().KeyCtrl)
        {
            static double last_mouse_x = ImPlot::GetPlotMousePos().x;
            static int last_tooltip_index = 0;
            double mouse_x = ImPlot::GetPlotMousePos().x;
            int tooltip_index = 0;
            if (last_mouse_x != mouse_x)
            {
                tooltip_index = GetBinarySearchIndex(plotData.xs, mouse_x);
            }
            else
            {
                tooltip_index = last_tooltip_index;
            }
            last_mouse_x = mouse_x;
            last_tooltip_index = tooltip_index;

            if (tooltip_index != -1)
            {
                double y_value = plotData.ys[tooltip_index];
                std::string msg = data_name + ":" + (FormatDoubleValue(y_value, 2));
                ImPlot::PlotText(msg.data(), mouse_x, y_value, ImVec2(0, 0), ImPlotTextFlags_None);
            }
        }

        if (ImPlot::BeginDragDropSourceItem(data_name.data()))
        {
            ImGui::SetDragDropPayload("MY_DND", data_name.data(), data_name.size() * sizeof(data_name[0]));
            ImPlot::ItemIcon(plotData.color);
            ImGui::SameLine();
            ImGui::TextUnformatted(data_name.data());
            ImPlot::EndDragDropSource();
        }
    }
    void PlotLayer::DrawTooltips()
    {
        const auto &dragX1 = m_uiContext->dragX1;
        const auto &dragX2 = m_uiContext->dragX2;
        const auto &isShowDragX1 = m_uiContext->isShowDragX1;
        const auto &isShowDragX2 = m_uiContext->isShowDragX2;
        CHECK_RETURN(!isShowDragX1 || !isShowDragX2);
        if (ImGui::BeginTooltip())
        {
            const double deltaX = dragX2 - dragX1;
            ImGui::Text("deltaX is %s", FormatDoubleValue(deltaX, 2).c_str());

            ImGui::EndTooltip();
        }
    }
    void PlotLayer::SetUpPlotAxis()
    {
        ImPlotAxisFlags flag = ImPlotAxisFlags_None;
        if (m_uiContext->autoFit)
        {
            flag = ImPlotAxisFlags_AutoFit;
        }
        {
            ImPlot::SetupAxis(ImAxis_Y1, nullptr, flag);
            ImPlot::SetupAxisLimits(ImAxis_Y1, -1000.0f, 1000.0f);
        }

        {
            ImPlot::SetupAxis(ImAxis_Y2, nullptr, ImPlotAxisFlags_AuxDefault | flag);
            ImPlot::SetupAxisLimits(ImAxis_Y2, -10, 10);
            ImPlot::SetupAxisLimitsConstraints(ImAxis_Y2, -500000, 500000);
        }
        {
            ImPlot::SetupAxis(ImAxis_Y3, nullptr, ImPlotAxisFlags_AuxDefault | flag);
            ImPlot::SetupAxisLimits(ImAxis_Y3, -1, 1);
            ImPlot::SetupAxisLimitsConstraints(ImAxis_Y3, -500000, 500000);
        }

        ImPlot::SetupAxis(ImAxis_X1, nullptr, flag);
        ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, 0, 10000);
    }
    void PlotLayer::SetPlotDragDropTarget(const char *title)
    {
        auto &plotDataList = m_scene->GetDoubleDataList();
        if (ImPlot::BeginDragDropTargetPlot())
        {
            const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("MY_DND");

            if (payload)
            {
                const char *name = (const char *)payload->Data;
                plotDataList[name].isPlt = true;
                plotDataList[name].yax = ImAxis_Y1;
                plotDataList[name].plotChartName = title;
            }
            ImPlot::EndDragDropTarget();
        }
        for (int y = ImAxis_Y1; y <= ImAxis_Y3; ++y)
        {
            if (ImPlot::BeginDragDropTargetAxis(y))
            {
                const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("MY_DND");
                if (payload)
                {
                    const char *name = (const char *)payload->Data;
                    plotDataList[name].isPlt = true;
                    plotDataList[name].yax = y;
                    plotDataList[name].plotChartName = title;
                }
                ImPlot::EndDragDropTarget();
            }
        }
    }
    void PlotLayer::DrawDragBar(const char *title, double min, double max, double *value, float *col, bool *is_show)
    {
        ImGui::Text("Visable %s", title);
        ImGui::SameLine();
        ImGui::Checkbox(("##" + std::string(title) + "check").data(), is_show);
        ImGui::SameLine();
        ImGui::ColorEdit4((std::string(title) + "color").data(), col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
        ImGui::SameLine();
        ImGui::SliderScalar(("##" + std::string(title)).data(), ImGuiDataType_Double, value, &min, &max);
        ImGui::SetItemUsingMouseWheel();
        if (ImGui::IsItemHovered())
        {
            float wheel = ImGui::GetIO().MouseWheel;
            if (wheel)
            {
                if (ImGui::IsItemActive())
                {
                    ImGui::ClearActiveID();
                }
                else
                {
                    double tmp = *value + ImSign(wheel) * 0.05;
                    *value = XVIZ_CLAMP(tmp, min, max);
                }
            }
        }
    }
    void PlotLayer::DrawDragLineTagX(const char *title, double *value, const ImVec4 &color, int id, double min, double max)
    {

        ImPlot::TagX(*value, color, "%s", title);
        ImPlot::DragLineX(id, value, color);
        *value = XVIZ_CLAMP(*value, min, max);
    }
}
