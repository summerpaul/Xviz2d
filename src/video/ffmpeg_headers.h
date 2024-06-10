/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:30:09
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-10 14:06:11
 */
#include <stdint.h>

#ifndef __FFMPEG_HEADERS_H__
#define __FFMPEG_HEADERS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define __STDC_CONSTANT_MACROS

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/time.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>

#include <libavutil/file.h>
#include <libavdevice/avdevice.h>
#include <libavutil/frame.h>

#ifdef __cplusplus
}
#endif

#endif /* __FFMPEG_HEADERS_H__ */
