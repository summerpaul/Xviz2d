/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:34:29
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-08 18:19:40
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

        if (avformat_open_input(&m_pAvFormatCtx, url.data(), NULL, &opts) != 0)
        {

            LOG_ERROR("Could't open video url");
            return false;
        }
        avformat_find_stream_info(m_pAvFormatCtx, NULL);
        int totalMs = m_pAvFormatCtx->duration / (AV_TIME_BASE / 1000);

        LOG_INFO("total time : %dms", totalMs);

        /** @brief echo format info */
        av_dump_format(m_pAvFormatCtx, 0, NULL, false);

        AVCodecParameters *av_codec_params;
        const AVCodec *av_codec;
        AVStream *av_stream;

        for (uint32_t i = 0; i < m_pAvFormatCtx->nb_streams; ++i)
        {
            av_stream = m_pAvFormatCtx->streams[i];
            av_codec_params = m_pAvFormatCtx->streams[i]->codecpar;
            av_codec = avcodec_find_decoder(av_codec_params->codec_id);
            if (!av_codec)
            {
                continue;
            }

            if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_videoStreamIndex = i;
                m_width = av_codec_params->width;
                m_height = av_codec_params->height;
                m_timeBase = m_pAvFormatCtx->streams[i]->time_base;
                break;
            }
        }

        if (m_videoStreamIndex == -1)
        {

            LOG_ERROR("Couldn't find valid video stream from url");
            return false;
        }

        // Set up a codec context for the decoder
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

        m_pAvFrame = av_frame_alloc();
        if (!m_pAvFrame)
        {
            LOG_ERROR("Couldn't allocate AVFrame");
            return false;
        }
        m_pAvPacket = av_packet_alloc();
        if (!m_pAvPacket)
        {
            LOG_ERROR("Couldn't allocate AVPacket");
            return false;
        }
        LOG_INFO("libCapture open url success.");
        return true;
    }

    bool VideoCapture::Decode(uint8_t *frame, int64_t *pts)
    {
        int response;
        char errStr[256] = {0};
        while (av_read_frame(m_pAvFormatCtx, m_pAvPacket) >= 0)
        {
            if (m_pAvPacket->stream_index != m_videoStreamIndex)
            {
                av_packet_unref(m_pAvPacket);
                continue;
            }
            response = avcodec_send_packet(m_pAvCodecCtx, m_pAvPacket);
            if (response < 0)
            {
                av_strerror(response, errStr, sizeof(errStr));
                LOG_ERROR("Failed to decode packet: %s\n", errStr);
                return false;
            }
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

        *pts = m_pAvFrame->pts;

        m_pSwsScalerCtx = sws_getContext(m_pAvFrame->width, m_pAvFrame->height, m_pAvCodecCtx->pix_fmt,
                                         m_pAvFrame->width, m_pAvFrame->height, AV_PIX_FMT_RGBA,
                                         SWS_BILINEAR, NULL, NULL, NULL);
        if (!m_pSwsScalerCtx)
        {
            LOG_ERROR("Coudldn't initialize sw scaler\n");

            return false;
        }

        uint8_t *dest[4] = {frame, NULL, NULL, NULL};
        int dest_linesize[4] = {m_pAvFrame->width * 4, 0, 0, 0};
        sws_scale(m_pSwsScalerCtx, m_pAvFrame->data, m_pAvFrame->linesize, 0, m_pAvFrame->height, dest, dest_linesize);
        sws_freeContext(m_pSwsScalerCtx);

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