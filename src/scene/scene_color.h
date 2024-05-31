/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 10:13:09
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 17:00:50
 */
#include <stdint.h>

#ifndef __SCENE_COLOR_H__
#define __SCENE_COLOR_H__

#include "basis/data_types.h"
#include <imgui.h>
namespace scene
{
    const unsigned int IM_WHITE = IM_COL32(255, 255, 255, 255);
    const unsigned int IM_RED = IM_COL32(255, 0, 0, 255);
    const unsigned int IM_GREEN = IM_COL32(0, 255, 0, 255);
    const unsigned int IM_BLUE = IM_COL32(0, 0, 255, 255);
    const unsigned int IM_BLACK = IM_COL32(0, 0, 0, 255);
    const unsigned int IM_YELLOW = IM_COL32(255, 255, 0, 255);
    const unsigned int IM_CYAN = IM_COL32(0, 255, 255, 255);
    const unsigned int IM_MAGENTA = IM_COL32(255, 0, 255, 255);
    const unsigned int IM_GRAY = IM_COL32(128, 128, 128, 255);
    const unsigned int IM_PURPLE = IM_COL32(128, 0, 128, 255);
    const unsigned int IM_PINK = IM_COL32(255, 192, 203, 255);
    const unsigned int IM_LIGHT_BLUE = IM_COL32(173, 216, 230, 255);
    const unsigned int IM_LIME_GREEN = IM_COL32(50, 205, 50, 255);
    const unsigned int IM_SLATE_GRAY = IM_COL32(112, 128, 144, 255);

    const unsigned int IM_COLORS[14]{
        IM_WHITE,
        IM_RED,
        IM_GREEN,
        IM_BLUE,
        IM_BLACK,
        IM_YELLOW,
        IM_CYAN,
        IM_MAGENTA,
        IM_GRAY,
        IM_PURPLE,
        IM_PINK,
        IM_LIGHT_BLUE,
        IM_LIME_GREEN,
        IM_SLATE_GRAY};

    inline unsigned int GetImColor(const basis::COLOR_TYPE &type)
    {
        return IM_COLORS[int(type)];
    }

} // namespace scene

#endif /* __SCENE_COLOR_H__ */
