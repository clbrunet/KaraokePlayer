#include <iostream>

#include <glad/gl.h>
#include <stb_image.h>

#include "Image.hpp"

Image::Image(const char* path)
{
    load(path);
}

Image::~Image()
{
    glDeleteTextures(1, &m_texture);

}

bool Image::load(const char* path)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels_count, 0);
    if (!data)
    {
        std::cerr << "Coundl't load the image '" << path << "'" << std::endl;
        return false;
    }

    if (m_channels_count != 3 && m_channels_count != 4)
    {
        stbi_image_free(data);
        std::cerr << "Only 3 or 4 image channels count is supported" << std::endl;
        return false;
    }
    if (m_channels_count == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR,
                GL_UNSIGNED_BYTE, data);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA,
                GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);
    return true;
}

unsigned int Image::texture() const
{
    return m_texture;
}
