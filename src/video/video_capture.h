/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:34:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-10 17:34:21
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
        // 打开视频
        bool Open(const std::string &url);
        // 视频解码
        bool Decode(uint8_t *frame, int64_t *pts, float speed = 1.0f);
        bool Close();

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }

        // 获取视频长度ms
        int GetDuration() const { return m_duration; }
        // 获取视频长度seconds
        float GetDurationSecond() const { return m_durationSecond; }

        AVRational GetTimeBase() const { return m_timeBase; }
        double GetTimeBaseDouble() const { return m_timeBaseDouble; }

        // 获取视频帧率
        double GetFramerate() const { return m_framerate; }
        // 获取起始时间戳
        int64_t GetStartTime() const { return m_startPts; }
        // 获取起始时间戳
        double GetTimeSinceStartSeconds() const { return m_timeSinceStartSeconds; }
        // 获取视频格式
        std::string GetFormatName() const { return m_formatName; }
        // 获取视频编码格式
        std::string GetCodecIdStr() const { return m_codecIdStr; }
        // 获取视频像素格式
        std::string GetPixFmtName() const { return m_pixFmtName; }
    

    private:
        int m_width;
        int m_height;

        int m_videoStreamIndex;
        AVRational m_timeBase;
        double m_timeBaseDouble;
        AVFormatContext *m_pAvFormatCtx; // 格式上下文
        AVCodecContext *m_pAvCodecCtx;   // 解析器上下文
        AVFrame *m_pAvFrame;             // 存储原始图像或音频数据的主要容器
        AVPacket *m_pAvPacket;           // 处理数据包
        SwsContext *m_pSwsScalerCtx;     // 像素缩放和像素格式转换结构体
        int m_duration;                  // ms
        double m_durationSecond;         // seconds
        int m_nbStreams;                 // number of streams
        double m_framerate;              // framerate
        int64_t m_startPts;              // 微秒（1/1,000,000秒）
        double m_timeSinceStartSeconds;
        std::string m_formatName;
        std::string m_codecIdStr;
        std::string m_pixFmtName;
        // int m_nbStreams
    };
}

#endif /* __VIDEO_CAPTURE_H__ */
