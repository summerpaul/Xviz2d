/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:02:30
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 14:40:16
 */
#include <stdint.h>

#ifndef __PLOT_LAYER_H__
#define __PLOT_LAYER_H__

#include "base_layer.h"
#include "scene/rolling_buffer.h"
namespace scene
{
    class SceneManager;

} // namespace scene

using namespace scene;

namespace ui
{

    class PlotLayer : public BaseLayer
    {
    public:
        PlotLayer(const std::string &name);
        virtual void Draw() override;
        virtual bool Init() override;
        virtual void Shutdown() override;
        virtual void SetUIContext(const UIContext::Ptr &ui_context) override;
		void SetCurPlotTime(const double& t);

    private:
        void DrawTable();
        void DrawSelectedData(const char *title, const RollingBuffer &data);
        void DrawUnselectedData(const std::string &title, const RollingBuffer &data);
        void DrawCharts(const char *title);
        void DrawSingleChart(const char *title);
        void DrawSinglePlotData(const std::string &title, const std::string &data_name, RollingBuffer &data);
        void DrawTooltips();
        void SetUpPlotAxis();
        void SetPlotDragDropTarget(const char *title);
        void DrawDragBar(const char *title, double min, double max, double *value, float *col, bool *is_show);
        void DrawDragLineTagX(const char *title, double *value, const ImVec4 &color, int id, double min, double max);

    protected:
        UIContext::Ptr m_pUiContext;
        std::shared_ptr<scene::SceneManager> m_pScene;
		bool m_setCurPlotTime = false;
    };

} // namespace ui

#endif /* __PLOT_LAYER_H__ */
