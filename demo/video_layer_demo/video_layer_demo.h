/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 17:50:37
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-08 23:23:37
 */
#include <stdint.h>

#ifndef __VIDEO_LAYER_DEMO_H__
#define __VIDEO_LAYER_DEMO_H__

#include "ui/base_layer.h"
#include "video/texture.h"
#include "video/video_capture.h"
#include <vector>
#include <string>
#include <mutex>
#include <thread>

using namespace ui;
using namespace video;
class VideoLayer : public BaseLayer
{
public:
    explicit VideoLayer(const std::string &name);
    ~VideoLayer() override;
    virtual void Draw() override;
    virtual bool Init() override;
    virtual void SetUIContext(const UIContext::Ptr &ui_context) override;
    virtual void FilesDropCallback(int count, const char **paths) override;
    virtual void Shutdown() override;

    void StartPlay();
    void StopPlay();
    void OnImGuiRender();
    void OnRender();


    void VideoPlayProcess();

private:
    std::unique_ptr<Texture> m_pTexTure;
    std::unique_ptr<VideoCapture> m_pVideoCapture;
    std::vector<uint8_t> m_FrameBuffer;
    std::vector<std::vector<uint8_t>> m_FrameBufferList;
    uint8_t *m_pData;
    int64_t m_pts;
    std::string m_url;
    bool isStartCapture;
    bool isStart;
    bool isDcodeSucceed;
    int m_width, m_height;
    std::mutex dataMutex;
    std::thread m_thread;
    bool m_running = false;
};

#endif /* __VIDEO_LAYER_DEMO_H__ */
