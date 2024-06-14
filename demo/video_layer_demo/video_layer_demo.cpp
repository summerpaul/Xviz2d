/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 17:50:41
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-11 12:05:00
 */
#include <iostream>
#include "video_layer_demo.h"
#include "icon/IconsFontAwesome6.h"
#include "basis/file.h"

using namespace basis;

VideoLayer::VideoLayer(const std::string &name) : BaseLayer(name) {}

VideoLayer::~VideoLayer()
{
    m_running = false;
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
bool VideoLayer::Init()
{
    m_pTexTure = std::make_unique<Texture>();
    m_pVideoCapture = std::make_unique<VideoCapture>();
    m_running = true;
    m_thread = std::thread(&VideoLayer::VideoPlayProcess, this);

    return true;
}

void VideoLayer::VideoPlayProcess()
{
    while (m_running)
    {
        // 重新播放
        if (m_isStart == true && m_isStartCapture == false)
        {
            StartPlay();
        }
        // 停止播放那风格
        else if (m_isStart == false && m_isStartCapture == true)
        {
            StopPlay();
        }
        // 视频播放
        if (m_isPause)
        {
            continue;
        }

        if (m_isStartCapture)
        {
            int length = m_width * m_height * 4;
            if (!m_pData)
            {
                continue;
            }

            m_pData = (uint8_t *)realloc(m_pData, length);
            m_tictoc.Tic();
            m_isDcodeSucceed = m_pVideoCapture->Decode(m_pData, &m_pts);
            m_decodeCostTime = m_tictoc.Toc();

            if (m_isDcodeSucceed)
            {
                m_dataMutex.lock();
                std::vector<uint8_t> rgbData(m_pData, m_pData + length);
                m_FrameBufferList.push_back(std::move(rgbData));
                if (m_FrameBufferList.size() > 2)
                { // set max buffer size
                    m_FrameBufferList.pop_back();
                }
                m_dataMutex.unlock();
                // 视频sleep
                //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }

    if (m_isStartCapture)
    {
        StopPlay();
    }
}
// 绘制ui
void VideoLayer::Draw()
{

    ImGui::Begin(m_name.data());

    if (ImGui::Button("start"))
    {
        m_isStart = true;
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    {
        ImGui::SetTooltip("Start play rtps video.");
    }
    ImGui::SameLine();
    if (ImGui::Button("stop"))
    {
        m_isStart = false;
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    {
        ImGui::SetTooltip("Stop play rtps video.");
    }
    ImGui::SameLine();
    if (ImGui::Button("pause"))
    {
        Pause();
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    {
        ImGui::SetTooltip("Pause play rtps video.");
    }
    ImGui::SameLine();
    if (ImGui::Button("resume"))
    {
        Resume();
    }

    ImGui::Text("Player Status:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(255, 0, 0, 255), "%s", (m_isStart ? "Start" : "Stop"));
    ImGui::SameLine();
    ImGui::Text("File Name:%s", m_fileName.c_str());

    ImGui::Text("decode cost time :%f", m_decodeCostTime);
    ImGui::SameLine();
    ImGui::Text("render cost time :%f", m_renderCostTime);
    // s

    const float video_duration = m_pVideoCapture->GetDurationSecond();
    m_videoPosition = m_pVideoCapture->GetTimeSinceStartSeconds();
    ImGui::SliderFloat(" ", &m_videoPosition, 0.0f, video_duration, "%.2f");

    OnImGuiRender();

    m_tictoc.Tic();
    OnRender();
    m_renderCostTime = m_tictoc.Toc();
    ImGui::End();
}

void VideoLayer::OnImGuiRender()
{
    // 进行视频的渲染
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if (m_isStartCapture)
    {
        ImGui::Image((ImTextureID)(intptr_t)m_pTexTure->getId(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 0), ImVec2(1, 1));
    }

    else
    {
        ImGui::Image((ImTextureID)(intptr_t)0, ImVec2(viewportSize.x, viewportSize.y), ImVec2(1, 1), ImVec2(1, 1));
    }
}

void VideoLayer::OnRender()
{
    if (m_isPause)
    {
        return;
    }
    if (!m_FrameBufferList.empty())
    {
        m_dataMutex.lock();
        m_FrameBuffer = m_FrameBufferList.back();
        m_pTexTure->bind(m_width, m_height, m_FrameBuffer.data());
        m_FrameBufferList.pop_back();
        m_dataMutex.unlock();
    }
}
void VideoLayer::SetUIContext(const UIContext::Ptr &ui_context) {}

void VideoLayer::FilesDropCallback(int count, const char **paths)
{
    if (count > 0)
    {
        m_url = paths[0];
        m_fileName = GetFileName(m_url) + "." + GetFileTag(m_url);
    }
}
void VideoLayer::Shutdown() {}

void VideoLayer::StartPlay()
{
    bool re = false;
    m_pVideoCapture->Init();
    re = m_pVideoCapture->Open(m_url);
    if (!re)
    {
        m_isStart = false;
        return;
    }
    m_pData = (uint8_t *)malloc(0);
    m_width = m_pVideoCapture->GetWidth();
    m_height = m_pVideoCapture->GetHeight();
    m_isStartCapture = true;
}
void VideoLayer::StopPlay()
{
    m_isStartCapture = false;
    m_pVideoCapture->Close();
    if (m_pData)
    {
        free(m_pData);
    }

    m_pData = nullptr;
}

void VideoLayer::Resume()
{
    m_isPause = false;
}

void VideoLayer::Pause()
{
    m_isPause = true;
}
