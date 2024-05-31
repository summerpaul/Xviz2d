/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 19:07:49
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:58:16
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <ctime>
#include <cstdio>
#include <string>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

#include "xviz_time.h"

using namespace basis;

#if (_WIN32 || WIN64)
#define MYFILE(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#else
#define MYFILE(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#endif

// 日志打印颜色
#define LOG_COLOR_NONE "\033[m"
#define LOG_COLOR_RED "\033[0;32;31m"
#define LOG_COLOR_GREEN "\033[0;32;32m"
#define LOG_COLOR_LIGHT_GREEN "\033[1;32m"
#define LOG_COLOR_BLUE "\033[0;32;34m"
#define LOG_COLOR_LIGHT_BLUE "\033[1;34m"
#define LOG_COLOR_DARY_GRAY "\033[1;30m"
#define LOG_COLOR_CYAN "\033[0;36m"
#define LOG_COLOR_LIGHT_CYAN "\033[1;36m"
#define LOG_COLOR_PURPLE "\033[0;35m"
#define LOG_COLOR_LIGHT_PURPLE "\033[1;35m"
#define LOG_COLOR_BROWN "\033[0;33m"
#define LOG_COLOR_YELLOW "\033[1;33m"
#define LOG_COLOR_LIGHT_GRAY "\033[0;37m"
#define LOG_COLOR_WHITE "\033[1;37m"

#define LOG_FATAL(fmt, ...) printf(LOG_COLOR_RED "[%s] [FATAL] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf(LOG_COLOR_PURPLE "[%s] [ERROR] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) printf(LOG_COLOR_YELLOW "[%s] [WARN] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...) printf(LOG_COLOR_LIGHT_GREEN "[%s] [NOTICE] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf(LOG_COLOR_GREEN "[%s] [INFO] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) printf(LOG_COLOR_LIGHT_BLUE "[%s] [DEBUG] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) printf(LOG_COLOR_CYAN "[%s] [TRACE] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)

#define LOG_LEVEL_FATAL 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_NOTICE 3
#define LOG_LEVEL_INFO 4
#define LOG_LEVEL_DEBUG 5
#define LOG_LEVEL_TRACE 6

#define LOG_LEVEL_PRINT(level, fmt, ...) \
    if (level == LOG_LEVEL_FATAL)        \
    {                                    \
        LOG_FATAL(fmt, ##__VA_ARGS__);   \
    }                                    \
    else if (level == LOG_LEVEL_ERROR)   \
    {                                    \
        LOG_ERROR(fmt, ##__VA_ARGS__);   \
    }                                    \
    else if (level == LOG_LEVEL_WARN)    \
    {                                    \
        LOG_WARN(fmt, ##__VA_ARGS__);    \
    }                                    \
    else if (level == LOG_LEVEL_NOTICE)  \
    {                                    \
        LOG_NOTICE(fmt, ##__VA_ARGS__);  \
    }                                    \
    else if (level == LOG_LEVEL_INFO)    \
    {                                    \
        LOG_INFO(fmt, ##__VA_ARGS__);    \
    }                                    \
    else if (level == LOG_LEVEL_DEBUG)   \
    {                                    \
        LOG_DEBUG(fmt, ##__VA_ARGS__);   \
    }                                    \
    else if (level == LOG_LEVEL_TRACE)   \
    {                                    \
        LOG_TRACE(fmt, ##__VA_ARGS__);   \
    }

// 返回打印日志
#define CHECK_RETURN_LOG(state, level, fmt, ...)   \
    if (state)                                     \
    {                                              \
        LOG_LEVEL_PRINT(level, fmt, ##__VA_ARGS__) \
        return;                                    \
    }

#define CHECK_CONTINUE_LOG(state, level, fmt, ...) \
    if (state)                                     \
    {                                              \
        LOG_LEVEL_PRINT(level, fmt, ##__VA_ARGS__) \
        continue;                                  \
    }

#define CHECK_BREAK_LOG(state, level, fmt, ...)    \
    if (state)                                     \
    {                                              \
        LOG_LEVEL_PRINT(level, fmt, ##__VA_ARGS__) \
        break;                                     \
    }

#define CHECK_RETURN_RET_LOG(state, ret, level, fmt, ...) \
    if (state)                                        \
    {                                                 \
        LOG_LEVEL_PRINT(level, fmt, ##__VA_ARGS__)    \
        return ret;                                   \
    }

#endif /* __LOGGER_H__ */
