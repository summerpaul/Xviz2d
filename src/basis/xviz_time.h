/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 15:12:08
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-31 22:41:19
 */
#include <stdint.h>

#ifndef __XVIZ_TIME_H__
#define __XVIZ_TIME_H__

#include <ctime>
#include <cstdio>
#include <string>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>



namespace basis
{

    inline std::string GetCurTimeStr()
    {
        auto now = std::chrono::system_clock::now();

        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        std::tm localTime;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
        localtime_s(&localTime, &currentTime);
#else
        localTime = *std::localtime(&currentTime);
#endif
        std::stringstream ss;
        ss << std::put_time(&localTime, "%Y-");
        ss << std::put_time(&localTime, "%m-");
        ss << std::put_time(&localTime, "%d ");
        ss << std::put_time(&localTime, "%H:");
        ss << std::put_time(&localTime, "%M:");
        ss << std::put_time(&localTime, "%S.");
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        ss << std::setfill('0') << std::setw(3) << milliseconds.count();
        return ss.str();
    }

    // 毫秒转时间戳
    inline double ConvertToTimestamp(int year, int month, int day, int hour, int minute, int second, int millisecond)
    {
        std::tm timeStruct = {};
        timeStruct.tm_year = year - 1900; // Year since 1900
        timeStruct.tm_mon = month - 1;    // Month since January (0-11)
        timeStruct.tm_mday = day;         // Day of the month (1-31)
        timeStruct.tm_hour = hour;        // Hour of the day (0-23)
        timeStruct.tm_min = minute;       // Minute within the hour (0-59)
        timeStruct.tm_sec = second;       // Second within the minute (0-59)
        timeStruct.tm_isdst = -1;         // Let mktime determine if DST is in effect

        // Convert to timestamp in seconds
        double timestamp = std::mktime(&timeStruct) + millisecond / 1000.0;
        return timestamp;
    }

    inline double GetTimeNow()
    {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        return double(0.001 * ms.count());
    }
} // namespace basis

#endif /* __XVIZ_TIME_H__ */
