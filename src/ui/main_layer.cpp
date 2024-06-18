/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 19:02:48
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-30 15:22:31
 */
#include <iostream>
#include "basis/logger.h"

#include "basis/defines.h"
#include "scene/scene_manager.h"

#include "scene_layer.h"
#include "plot_layer.h"
#include "scene_edit_layer.h"
#include "main_layer.h"

#include "icon/IconsFontAwesome6.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "app/app.h"
namespace ui
{

    MainLayer::MainLayer(const std::string &name) : BaseLayer(name)
    {
    }
    bool MainLayer::Init()
    {
        m_uiContext = std::make_shared<UIContext>();
        m_sceneLayer = std::make_shared<SceneLayer>("SceneLayer");
        CHECK_RETURN_RET(!m_sceneLayer->Init(), false);
        AddLayer(m_sceneLayer);
        m_plotLayer = std::make_shared<PlotLayer>("PlotLayer");
        CHECK_RETURN_RET(!m_plotLayer->Init(), false);
        AddLayer(m_plotLayer);
        m_sceneEditLayer = std::make_shared<SceneEditLayer>("SceneEditLayer");
        CHECK_RETURN_RET(!m_sceneEditLayer->Init(), false);
        AddLayer(m_sceneEditLayer);
        LOG_INFO("Main Layer Init");
        return true;
    }

    bool MainLayer::InitHandle(GLFWwindow *window)
    {
        CHECK_RETURN_RET(window == nullptr, false);
        const char *glsl_version = "#version 330";
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        InitStyle();
        InitFontAndIcon();
        CHECK_RETURN_RET(!ImGui_ImplGlfw_InitForOpenGL(window, true), false);
        CHECK_RETURN_RET(!ImGui_ImplOpenGL3_Init(glsl_version), false);
        LOG_INFO("Init Handle");
        return true;
    }

    void MainLayer::InitStyle()
    {
        ImGuiStyle &styl = ImGui::GetStyle();
        styl.GrabMinSize = 7;
        styl.FrameBorderSize = 0;
        styl.SeparatorTextBorderSize = 1;
        styl.DisplaySafeAreaPadding = {0, 0};
        styl.WindowPadding = {6, 6};
        styl.ScrollbarSize = 10;
        styl.ScrollbarRounding = 2;
        styl.TabBarBorderSize = 1;
        styl.TabRounding = 2;
        styl.FramePadding = {8, 2};
        styl.FrameRounding = 2;

        auto &Col = styl.Colors;
        Col[ImGuiCol_HeaderHovered] = {0.051f, 0.431f, 0.992f, 1.000f};
        Col[ImGuiCol_HeaderActive] = {0.071f, 0.388f, 0.853f, 1.000f};
        Col[ImGuiCol_Border] = {0.090f, 0.090f, 0.094f, 1.000f};
        Col[ImGuiCol_TabActive] = {0.234f, 0.234f, 0.243f, 1.000f};
        Col[ImGuiCol_PopupBg] = {0.123f, 0.123f, 0.123f, 0.940f};
        Col[ImGuiCol_TitleBg] = {0.131f, 0.135f, 0.135f, 1.000f};
        Col[ImGuiCol_MenuBarBg] =
            Col[ImGuiCol_TitleBgActive] = {0.118f, 0.118f, 0.119f, 1.000f};
        Col[ImGuiCol_Header] = {0.106f, 0.298f, 0.789f, 1.000f};
        Col[ImGuiCol_CheckMark] =
            Col[ImGuiCol_SliderGrab] =
                {1.000f, 1.000f, 1.000f, 1.000f};
    }

    void MainLayer::InitFontAndIcon()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        float baseFontSize = 18.0f;

        const char *fontPath = nullptr;

        const char *fontPath1 = "resources/font/msyh.ttf";

        const char *fontPath2 = "../resources/font/msyh.ttf";

        const char *iconPath = nullptr;

        const char *iconPath1 = "resources/icon/fa-solid-900.ttf";

        const char *iconPath2 = "../resources/icon/fa-solid-900.ttf";

        FILE *file1 = nullptr;
        FILE *file2 = nullptr;
        FILE *file3 = nullptr;
        FILE *file4 = nullptr;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
        fopen_s(&file1, fontPath1, "rb");
        fopen_s(&file2, fontPath2, "rb");

        fopen_s(&file3, iconPath1, "rb");
        fopen_s(&file4, iconPath2, "rb");
#else

        file1 = fopen(fontPath1, "rb");
        file2 = fopen(fontPath2, "rb");
        file3 = fopen(iconPath1, "rb");
        file4 = fopen(iconPath2, "rb");
#endif
        if (file1)
        {
            fontPath = fontPath1;
            fclose(file1);
        }

        if (file2)
        {
            fontPath = fontPath2;
            fclose(file2);
        }

        if (file3)
        {
            iconPath = iconPath1;
            fclose(file3);
        }

        if (file4)
        {
            iconPath = iconPath2;
            fclose(file4);
        }

        if (fontPath)
        {
            io.Fonts->AddFontFromFileTTF(
                fontPath,
                baseFontSize,
                NULL,
                io.Fonts->GetGlyphRangesChineseFull());
        }
        else
        {
            LOG_WARN("failed to load font");
        }

        if (iconPath)
        {
            float iconFontSize = baseFontSize * 2.0f / 3.0f;
            static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
            ImFontConfig icons_config;
            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.GlyphMinAdvanceX = iconFontSize;
            io.Fonts->AddFontFromFileTTF(
                iconPath,
                iconFontSize,
                &icons_config,
                icons_ranges);
        }
        else
        {
            LOG_WARN("failed to load icon");
        }
    }
    void MainLayer::Draw()
    {
        // layer draw
        for (const auto &layer : m_layers)
        {
            layer->Draw();
        }
    }

    void MainLayer::AddLayer(const BaseLayer::Ptr &layer)
    {
        CHECK_RETURN(layer == nullptr);
        m_layers.push_back(layer);
        layer->SetUIContext(m_uiContext);
    }

    void MainLayer::Shutdown()
    {
        for (const auto &layer : m_layers)
        {
            layer->Shutdown();
        }
        m_layers.clear();
    }

    void MainLayer::FilesDropCallback(int count, const char **paths)
    {
        for (auto &layer : m_layers)
        {
            layer->FilesDropCallback(count, paths);
        }
    }

	void MainLayer::SetCurPlotTime(const double& t)
	{
		m_plotLayer->SetCurPlotTime(t);
	
	}

    void MainLayer::DropCallback(GLFWwindow *window, int count, const char **paths)
    {
        app::App::GetInstance()->SetDropFiles(count, paths);
    }

    void MainLayer::DrawMenuBar()
    {
        auto scene = app::App::GetInstance()->GetSceneManager();
        const float fps = ImGui::GetIO().Framerate;
        if (ImGui::BeginMenuBar())
        {
            const auto &mouse_pose = scene->GetMousePose();
            const auto &dist = scene->GetMousePoseToOriginDist();
            ImGui::Text(ICON_FA_LOCATION_ARROW "[%.2f m, %.2f m, %.2f m]",
                        mouse_pose.x, mouse_pose.y, dist);
            ImGui::Separator();
            ImGui::Text(" %.2f fps", fps);
            ImGui::EndMenuBar();
        }
    }
    void MainLayer::BeginDraw()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // dockspace and menu bar
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", NULL, window_flags);
        ImGui::PopStyleVar(3);
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        DrawMenuBar();
        ImGui::End();
    }

    void MainLayer::EndDraw()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
