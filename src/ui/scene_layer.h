/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:00:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 14:10:31
 */

#ifndef __SCENE_LAYER_H__
#define __SCENE_LAYER_H__
#include "base_layer.h"

namespace scene
{
    class SceneManager;
}

namespace ui
{
    class SceneLayer : public BaseLayer
    {
    public:
        SceneLayer(const std::string &name);
        virtual void Draw() override;
        virtual bool Init() override;
        virtual void Shutdown() override;
        virtual void SetUIContext(const UIContext::Ptr &ui_context) override;

    private:
        void HandleMouse();
        void HandleZoomScroll(const ImGuiIO &io);
        void HandleMouseMenu();
        void HandleMeasure(const ImGuiIO &io);

    protected:
        std::shared_ptr<scene::SceneManager> m_scene;
        UIContext::Ptr m_uiContext;
    };
}
#endif /* __SCENE_LAYER_H__ */
