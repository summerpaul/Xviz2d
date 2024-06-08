/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 17:50:41
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-09 00:50:20
 */
#include <iostream>
#include "video_layer_demo.h"

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

        if (isStart == true && isStartCapture == false)
        {
            StartPlay();
        }
        else if (isStart == false && isStartCapture == true)
        {
            StopPlay();
        }

        if (isStartCapture)
        {
            int length = m_width * m_height * 4;
            m_pData = (uint8_t *)realloc(m_pData, length);
            m_pts = 1;
            isDcodeSucceed = m_pVideoCapture->Decode(m_pData, &m_pts);
            if (isDcodeSucceed)
            {
                dataMutex.lock();
                std::vector<uint8_t> rgbData(m_pData, m_pData + length);
                m_FrameBufferList.push_back(std::move(rgbData));
                if (m_FrameBufferList.size() > 2)
                { // set max buffer size
                    m_FrameBufferList.pop_back();
                }
                std::cout << "m_pts is " << m_pts << std::endl;
                std::cout << "StreamIndex is " << m_pVideoCapture->GetVideoStreamIndex() << std::endl;
                std::cout << "m_FrameBufferList.size() is " << m_FrameBufferList.size() << std::endl;
                dataMutex.unlock();
            }
        }
    }

    if (isStartCapture)
        StopPlay();
}
void VideoLayer::Draw()
{

    ImGui::Begin(m_name.data());
    ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.2f);
    ImGui::AlignTextToFramePadding();
    ImGui::NewLine();
    ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
    if (ImGui::Button(u8"开始", sz))
    {
        isStart = true;
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
        ImGui::SetTooltip("Start play rtps video.");

    if (ImGui::Button(u8"停止", sz))
    {
        isStart = false;
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
        ImGui::SetTooltip("Stop play rtps video.");

    ImGui::NewLine();
    ImGui::Text("Player Status:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(255, 0, 0, 255), "%s", (isStart ? "Start" : "Stop"));

    OnImGuiRender();
    OnRender();
    ImGui::End();
}

void VideoLayer::OnImGuiRender()
{
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if (isStartCapture)
        ImGui::Image((ImTextureID)(intptr_t)m_pTexTure->getId(), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 0), ImVec2(1, 1));
    else
        ImGui::Image((ImTextureID)(intptr_t)0, ImVec2(viewportSize.x, viewportSize.y), ImVec2(1, 1), ImVec2(1, 1));
}

void VideoLayer::OnRender()
{
    if (!m_FrameBufferList.empty())
    {
        dataMutex.lock();
        m_FrameBuffer = m_FrameBufferList.back();
        m_pTexTure->bind(m_width, m_height, m_FrameBuffer.data());
        m_FrameBufferList.pop_back();
        dataMutex.unlock();
    }
}
void VideoLayer::SetUIContext(const UIContext::Ptr &ui_context) {}
void VideoLayer::FilesDropCallback(int count, const char **paths)
{
    if (count > 0)
    {
        m_url = paths[0];
        // StartPlay();
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
        isStart = false;
        return;
    }
    m_pData = (uint8_t *)malloc(0);
    m_width = m_pVideoCapture->GetWidth();
    m_height = m_pVideoCapture->GetHeight();
    isStartCapture = true;
}
void VideoLayer::StopPlay()
{
    isStartCapture = false;
    m_pVideoCapture->Close();
    if (m_pData)
        free(m_pData);
    m_pData = nullptr;
}
