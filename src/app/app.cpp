/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 19:08:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 10:27:22
 */
#include "app.h"
#include "basis/logger.h"
#include "window/window.h"
#include "scene/scene_manager.h"
#include "ui/main_layer.h"
namespace app
{
    App::~App()
    {
        CHECK_RETURN(m_isShutDown);
        Shutdown();
        LOG_INFO("APP shutdown succeeded");
    }
    App *App::GetInstance()
    {
        static App app;
        return &app;
    }

    bool App::Init(const std::string &title, uint32_t width, uint32_t height)
    {
        m_pWindow = std::make_unique<window::Window>();
        CHECK_RETURN_RET(!m_pWindow->Init(width, height, title), false);
        m_pSceneManager = std::make_shared<scene::SceneManager>();
        CHECK_RETURN_RET(!m_pSceneManager->Init(), false);
        m_pMainUI = std::make_unique<ui::MainLayer>("MainLayer");
        CHECK_RETURN_RET(!m_pMainUI->Init(), false);
        CHECK_RETURN_RET(!m_pMainUI->InitHandle(m_pWindow->GetHandle()), false);
        LOG_INFO("APP init succeeded");
        return true;
    }

    void App::Run()
    {
        // 设置窗口回调函数
        m_pWindow->SetDropCallback(ui::MainLayer::DropCallback);
        while (!m_pWindow->ShouldClose())
        {
            m_pWindow->PrewDraw();
            m_pMainUI->BeginDraw();
            m_pMainUI->Draw();
            m_pMainUI->EndDraw();
            m_pWindow->PostDraw();
        }
    }

    void App::AddLayer(const std::shared_ptr<ui::BaseLayer> &layer)
    {
        m_pMainUI->AddLayer(layer);
    }

    void App::SetDropFiles(int count, const char **paths)
    {
        m_pMainUI->FilesDropCallback(count, paths);
    }

	void App::SetCurPlotTime(const double& t)
	{
		m_pMainUI->SetCurPlotTime(t);
	}

    void App::Shutdown()
    {
        m_pMainUI->Shutdown();
        m_pWindow->DestroyWindow();
        LOG_INFO("Shutting down");
        m_isShutDown = true;
    }

}