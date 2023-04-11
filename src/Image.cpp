#include <iostream>

#include <stb_image.h>

#include "Image.hpp"

Image::Image(const char* path)
{
    load(path);
}

Image::~Image()
{
    if (m_data)
    {
        stbi_image_free(m_data);
    }
}

bool Image::load(const char* path)
{
    m_data = stbi_load(path, &m_width, &m_height, &m_channelsCount, 0);
    if (!m_data)
    {
        std::cerr << "Coundl't load the image '" << path << "'" << std::endl;
        return false;
    }
    return true;
}
