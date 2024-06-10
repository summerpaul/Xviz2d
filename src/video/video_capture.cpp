/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:34:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-10 17:51:59
 */

#include "video_capture.h"
#include "basis/logger.h"
namespace video
{
    VideoCapture::VideoCapture()
    {
    }
    VideoCapture::~VideoCapture()
    {
    }

    void VideoCapture::Init()
    {
        m_videoStreamIndex = -1;
        m_pAvFormatCtx = nullptr;
        m_pAvCodecCtx = nullptr;
        m_pAvFrame = nullptr;
        m_pAvPacket = nullptr;
        m_pSwsScalerCtx = nullptr;
        // 初始化ffmpeg
        // 注册所有编码器
        avdevice_register_all();
        avformat_network_init();
        av_log_set_level(AV_LOG_FATAL);
        LOG_INFO("Initializing video capture successfully ...");
    }

    bool VideoCapture::Open(const std::string &url)
    {
        m_pAvFormatCtx = avformat_alloc_context();
        if (!m_pAvFormatCtx)
        {
            LOG_ERROR("Couldn't create AVFormatContext");
            return false;
        }

        /* options rtsp*/
        AVDictionary *opts = nullptr;
        av_dict_set(&opts, "rtsp_transport", "tcp", 0);
        av_dict_set(&opts, "buffer_size", "1024000", 0);
        av_dict_set(&opts, "stimeout", "10000000", 0);
        av_dict_set(&opts, "max_delay", "10000000", 0);
        // 打开输入视频文件
        if (avformat_open_input(&m_pAvFormatCtx, url.data(), NULL, &opts) != 0)
        {
            LOG_ERROR("Could't open video url");
            return false;
        }

        // 读取文件的元数据
        avformat_find_stream_info(m_pAvFormatCtx, NULL);
        // 视频的持续时间ms
        int totalMs = m_pAvFormatCtx->duration / (AV_TIME_BASE / 1000);
        // m_pAvFormatCtx->
        m_duration = totalMs;
        m_durationSecond = totalMs * 0.001f;
        LOG_INFO("total time : %dms", totalMs);
        av_dump_format(m_pAvFormatCtx, 0, NULL, false);
        // 视频解码器参数
        // codec_id：编码器类型
        // codec_tag：解码器标签
        // format ：像素或采样格式
        // bit_rate ：描述音视频流的质量
        // channels：音频流的通道数
        // sample_rate：音频流的采样率
        // avg_frame_rate：视频流的帧率
        AVCodecParameters *av_codec_params;
        const AVCodec *av_codec;
        AVStream *av_stream;
        m_nbStreams = m_pAvFormatCtx->nb_streams;

        for (uint32_t i = 0; i < m_nbStreams; ++i)
        {
            av_stream = m_pAvFormatCtx->streams[i];
            av_codec_params = m_pAvFormatCtx->streams[i]->codecpar;
            // 寻找相应的解码器
            av_codec = avcodec_find_decoder(av_codec_params->codec_id);
            if (!av_codec)
            {
                continue;
            }
            // 找到视频开始的时间与帧数（找到视频流的索引）
            if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_videoStreamIndex = i;
                m_width = av_codec_params->width;
                m_height = av_codec_params->height;
                m_timeBase = m_pAvFormatCtx->streams[i]->time_base;
                m_timeBaseDouble = av_q2d(m_timeBase);
                m_framerate = av_q2d(av_codec_params->framerate);
                m_startPts = m_pAvFormatCtx->streams[i]->start_time;
                m_formatName = m_pAvFormatCtx->iformat->name;
                m_codecIdStr = avcodec_get_name(m_pAvFormatCtx->streams[i]->codecpar->codec_id);
                m_pixFmtName = av_get_pix_fmt_name(AVPixelFormat(m_pAvFormatCtx->streams[i]->codecpar->format));

                break;
            }
        }
        // 视频无效
        if (m_videoStreamIndex == -1)
        {
            LOG_ERROR("Couldn't find valid video stream from url");
            return false;
        }

        // Set up a codec context for the decoder
        // 分配解码器上下文
        m_pAvCodecCtx = avcodec_alloc_context3(av_codec);
        if (!m_pAvCodecCtx)
        {

            LOG_ERROR("Couldn't create AVCodecContext");
            return false;
        }

        if (avcodec_parameters_to_context(m_pAvCodecCtx, av_codec_params) < 0)
        {
            LOG_ERROR("Couldn't initialize AVCodecContext");
            return false;
        }
        if (avcodec_open2(m_pAvCodecCtx, av_codec, NULL) < 0)
        {

            LOG_ERROR("CCouldn't open codec");
            return false;
        }
        // 为帧分配内存
        m_pAvFrame = av_frame_alloc();
        if (!m_pAvFrame)
        {
            LOG_ERROR("Couldn't allocate AVFrame");
            return false;
        }
        // 音频分配内存
        m_pAvPacket = av_packet_alloc();
        if (!m_pAvPacket)
        {
            LOG_ERROR("Couldn't allocate AVPacket");
            return false;
        }
        LOG_INFO("libCapture open url success.");
        return true;
    }

    bool VideoCapture::Decode(uint8_t *frame, int64_t *pts, float speed)
    {

        int response;
        char errStr[256] = {0};
        // 解码视频帧
        // 从输入文件中读取帧
        auto startTime = av_gettime();
        while (av_read_frame(m_pAvFormatCtx, m_pAvPacket) >= 0)
        {
            if (m_pAvPacket->stream_index != m_videoStreamIndex)
            {
                av_packet_unref(m_pAvPacket);
                continue;
            }
            // 倍速播放
            m_pAvPacket->pts = m_pAvPacket->pts / speed;
            m_pAvPacket->dts = m_pAvPacket->dts / speed;
            // 将解码器所需的压缩数据包（即AVPacket）发送给解码器
            response = avcodec_send_packet(m_pAvCodecCtx, m_pAvPacket);
            if (response < 0)
            {
                av_strerror(response, errStr, sizeof(errStr));
                LOG_ERROR("Failed to decode packet: %s\n", errStr);
                return false;
            }
            // 从解码器中接受解码后的帧（即AVFrame）
            response = avcodec_receive_frame(m_pAvCodecCtx, m_pAvFrame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
            {
                av_packet_unref(m_pAvPacket);
                continue;
            }
            else if (response < 0)
            {
                av_strerror(response, errStr, sizeof(errStr));
                LOG_ERROR("Failed to decode packet: %s\n", errStr);
                return false;
            }
            av_packet_unref(m_pAvPacket);
            break;
        }
        auto pt_delta_t = m_pAvFrame->pts - *pts;
        *pts = m_pAvFrame->pts;
        int64_t time_since_start = m_pAvFrame->pts - m_startPts;
        m_timeSinceStartSeconds = (time_since_start)*m_timeBaseDouble;

        m_pSwsScalerCtx = sws_getContext(
            m_pAvFrame->width,      // 源图像宽
            m_pAvFrame->height,     // 源图像高
            m_pAvCodecCtx->pix_fmt, // 源图像像素格式
            m_pAvFrame->width,      // 目标图像宽
            m_pAvFrame->height,     // 目标图像高
            AV_PIX_FMT_RGBA,        // 目标图像格式
            SWS_BILINEAR,           // 差值算法
            NULL, NULL, NULL);
        if (!m_pSwsScalerCtx)
        {
            LOG_ERROR("Coudldn't initialize sw scaler\n");

            return false;
        }

        uint8_t *dest[4] = {frame, NULL, NULL, NULL};
        int dest_linesize[4] = {m_pAvFrame->width * 4, 0, 0, 0};

        // 执行缩放和格式转换
        sws_scale(m_pSwsScalerCtx, m_pAvFrame->data, m_pAvFrame->linesize, 0, m_pAvFrame->height, dest, dest_linesize);
        // 释放资源
        sws_freeContext(m_pSwsScalerCtx);

        // 延时(不然文件会立即全部播放完)
        int64_t nowTime = av_gettime() - startTime;
        if (pt_delta_t > nowTime && pt_delta_t < 30000)
        {
            av_usleep(pt_delta_t - nowTime);
        }

        return true;
    }

    bool VideoCapture::Close()
    {
        if (m_pAvCodecCtx)
        {
            avformat_close_input(&m_pAvFormatCtx);
            avformat_free_context(m_pAvFormatCtx);
        }
        if (m_pAvCodecCtx)
        {
            avcodec_free_context(&m_pAvCodecCtx);
        }
        if (m_pAvPacket)
        {
            av_free(m_pAvPacket);
        }
        if (m_pAvFrame)
        {
            av_frame_free(&m_pAvFrame);
        }
        avformat_network_deinit();
        return true;
    }
}