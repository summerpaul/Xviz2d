/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 17:45:16
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 13:35:57
 */
#include <stdint.h>

#ifndef __UI_CONTEXT_H__
#define __UI_CONTEXT_H__
#include <memory>
#include <implot.h>
namespace ui
{
    struct UIContext
    {

        void ResetDragData()
        {
            dragX1 = 0.0f;
            dragX2 = 0.0f;
            idx1 = 0;
            idx2 = 0;
            lastDragX1 = 0.0f;
            lastDragX2 = 0.0f;
        }
        typedef std::shared_ptr<UIContext> Ptr;
        // 绘图相关
        int rows = 1;
        int cols = 1;
        float rratios[6] = {1, 1, 1, 1, 1, 1};
        float cratios[6] = {1, 1, 1, 1, 1, 1};
        double dragX1 = 0.0;
        double dragX2 = 0.0;
        double lastDragX1;
        double lastDragX2;
        ImVec4 dragX1Color = ImVec4(0, 0.5, 0.5, 1);
        ImVec4 dragX2Color = ImVec4(0.5, 0.5, 0, 1);
        bool isShowDragX1 = false;
        bool isShowDragX2 = false;
        int idx1 = 0;
        int idx2 = 0;
        ImPlotRect lims{0, 1, 0, 1};
        bool linkx = true;
        double maxX = 10000;
        bool autoFit = true;
    };

} // namespace ui

#endif /* __UI_CONTEXT_H__ */
