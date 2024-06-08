/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 16:47:48
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-08 17:47:31
 */
#include <stdint.h>

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace video
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        void bind(int width, int height, uint8_t *rgbData);
        void unbind() const;
        inline int getId() const { return m_ID; }

    private:
        unsigned int m_ID;
    };
}
#endif /* __TEXTURE_H__ */
