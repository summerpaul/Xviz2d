/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-27 16:21:27
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-04-27 16:25:49
 */
#include <stdint.h>

#ifndef __SIL_UTIL_H__
#define __SIL_UTIL_H__

#include <fstream>

// 读取bin日志
template <typename LOG>
static std::ifstream &operator>>(std::ifstream &ifs, LOG &cs)
{
    ifs.read(reinterpret_cast<char *>(&cs), sizeof(LOG));
    return ifs;
}
// 保存bin日志
template <typename LOG>
static std::ofstream &operator<<(std::ofstream &ifs, LOG &cs)
{
    ifs.write(reinterpret_cast<char *>(&cs), sizeof(LOG));
    return ifs;
}

#endif /* __SIL_UTIL_H__ */
