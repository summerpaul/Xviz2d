/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:02:11
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 15:20:59
 */
#include <stdint.h>

#ifndef __SCENE_EDIT_LAYER_H__
#define __SCENE_EDIT_LAYER_H__

#include "base_layer.h"
namespace scene
{
    class SceneManager;
    struct SceneOptions;

} // namespace scene

namespace ui
{
    class SceneEditLayer : public BaseLayer
    {
    public:
        SceneEditLayer(const std::string &name);
        virtual void Draw() override;
        virtual bool Init() override;
        virtual void Shutdown() override;
        virtual void SetUIContext(const UIContext::Ptr &ui_context) override;

    private:
        void SceneEdit(std::shared_ptr<scene::SceneOptions> &options);
        void SceneGridEdit(std::shared_ptr<scene::SceneOptions> &options);
        void SceneOriginAxisEdit(std::shared_ptr<scene::SceneOptions> &options);
        void SceneViewEdit(std::shared_ptr<scene::SceneOptions> &options);
        void SceneObjectsEdit(std::shared_ptr<scene::SceneOptions> &options);

        void PlotUiContextEdit();
        void StyleEdit();

    protected:
        UIContext::Ptr m_uiContext;
        std::shared_ptr<scene::SceneManager> m_scene;
    };
}
#endif /* __SCENE_EDIT_LAYER_H__ */
