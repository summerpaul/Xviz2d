/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-27 19:53:40
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-27 19:55:46
 */

#ifndef __BOUND_BOX_H__
#define __BOUND_BOX_H__

namespace basis
{
    class BoundBox
    {

    public:
        float m_minX;
        float m_minY;
        float m_maxX;
        float m_maxY;
    };

} // namespace basis

#endif /* __BOUND_BOX_H__ */
