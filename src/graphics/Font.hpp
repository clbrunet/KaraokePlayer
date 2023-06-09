#pragma once

#include <pugixml.hpp>

#include "graphics/Image.hpp"
#include "math/Vec2.hpp"

class Font
{
public:
    Font() = default;
    Font(Font &&) = delete;
    Font(const Font &) = delete;
    Font &operator=(Font &&) = delete;
    Font &operator=(const Font &) = delete;
    ~Font() = default;

    Font(const char* xml_path, const char* image_path);

    bool load(const char* xml_path, const char* image_path);
    const Image& image() const;

    struct CharTextureCoordinates
    {
        Vec2 bottom_left;
        Vec2 top_right;
    };
    CharTextureCoordinates get_char_texture_coordinates(unsigned char c) const;

private:
    pugi::xml_document m_doc = pugi::xml_document();
    Image m_image;

    pugi::xml_node get_char_xml_node(unsigned char c) const;
};
