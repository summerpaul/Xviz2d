/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:34:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-09 00:49:26
 */
#include <stdint.h>

#ifndef __VIDEO_CAPTURE_H__
#define __VIDEO_CAPTURE_H__

#include "ffmpeg_headers.h"
#include <string>
namespace video
{
    class VideoCapture
    {
    public:
        VideoCapture();
        ~VideoCapture();
        void Init();
        bool Open(const std::string &url);
        bool Decode(uint8_t *frame, int64_t *pts);
        bool Close();

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        int GetVideoStreamIndex() const { return m_videoStreamIndex; }

    private:
        int m_width;
        int m_height;

        int m_videoStreamIndex;
        AVRational m_timeBase;
        AVFormatContext *m_pAvFormatCtx;
        AVCodecContext *m_pAvCodecCtx;
        AVFrame *m_pAvFrame;
        AVPacket *m_pAvPacket;
        SwsContext *m_pSwsScalerCtx;
    };
}

#endif /* __VIDEO_CAPTURE_H__ */
