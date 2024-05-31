/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:16:21
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:16:50
 */
#include <stdint.h>

#ifndef __SCENE_DRAW_H__
#define __SCENE_DRAW_H__

#include "scene_manager.h"
namespace scene
{

    void DrawScene(ImDrawList *drawList, const SceneManager::Ptr &scene);

} // name

#endif /* __SCENE_DRAW_H__ */
