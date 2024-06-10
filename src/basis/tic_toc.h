/**
 * @Author: Xia Yunkai
 * @Date:   2024-01-29 22:10:51
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-04-26 22:11:03
 */

#ifndef __X_ROBOTICS_TIC_TOC_H__
#define __X_ROBOTICS_TIC_TOC_H__
#include <chrono>

namespace basis
{
  class TicToc
  {
  public:
    TicToc() = default;
    ~TicToc() = default;
    void Tic() { m_start = std::chrono::system_clock::now(); }
    double Toc()
    {
      m_end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = m_end - m_start;
      return elapsed_seconds.count();
    }
    static double TimePointToDouble(
        const std::chrono::time_point<std::chrono::system_clock> &time_point)
    {
      auto tt = std::chrono::duration<double>(time_point.time_since_epoch());
      return tt.count();
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> m_start, m_end;
  };
}

#endif /* __TIC_TOC_H__ */
