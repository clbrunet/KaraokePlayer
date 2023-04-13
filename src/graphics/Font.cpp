#include <cstdlib>
#include <cstring>
#include <iostream>

#include "graphics/Font.hpp"

Font::Font(const char* xml_path, const char* image_path)
{
    load(xml_path, image_path);
}

bool Font::load(const char* xml_path, const char* image_path)
{
    if (!m_doc.load_file(xml_path))
    {
        std::cerr << "Coundl't load the font xml '" << xml_path << "'" << std::endl;
        return false;
    }
    if (!m_image.load(image_path))
    {
        return false;
    }
    return true;
}

const Image& Font::image() const
{
    return m_image;
}

Font::CharTextureCoordinates Font::get_char_texture_coordinates(unsigned char c) const
{
    pugi::xml_node question_mark_node;
    pugi::xml_node char_node;
    bool found = false;
    for (pugi::xml_node node : m_doc.child("font").child("chars"))
    {
        if (std::strcmp(node.name(), "char") != 0)
        {
            continue;
        }
        unsigned char current = std::atoi(node.attribute("id").value());
        if (current == '?')
        {
            question_mark_node = node;
        }
        if (current == c)
        {
            char_node = node;
            found = true;
            break;
        }
    }
    if (!found)
    {
        char_node = question_mark_node;
    }
    int offset_x = std::atoi(char_node.attribute("xoffset").value());
    int offset_y = std::atoi(char_node.attribute("xoffset").value());

    int start_x = std::atoi(char_node.attribute("x").value()) - offset_x;
    int start_y = m_image.height() - std::atoi(char_node.attribute("y").value()) - offset_y;
    int end_x = start_x + std::atoi(char_node.attribute("width").value()) + offset_x;
    int end_y = start_y - std::atoi(char_node.attribute("height").value()) + offset_y;

    Vec2 bottom_left((float)start_x / (float)m_image.width(),
            (float)end_y / (float)m_image.height());
    Vec2 top_right((float)end_x / (float)m_image.width(),
            (float)start_y / (float)m_image.height());
    return {
        .bottom_left = bottom_left,
        .top_right = top_right,
    };
}
