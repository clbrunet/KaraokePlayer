#ifndef FONT_HPP
#define FONT_HPP

#include <pugixml.hpp>

#include "Image.hpp"

class Font
{
public:
    Font() = default;
    Font(Font &&) = default;
    Font(const Font &) = delete;
    Font &operator=(Font &&) = default;
    Font &operator=(const Font &) = delete;
    ~Font();

    Font(const char* xml_path, const char* image_path);

    bool load(const char* xml_path, const char* image_path);

private:
    pugi::xml_document m_doc = pugi::xml_document();
    Image m_image = Image();
};

#endif
