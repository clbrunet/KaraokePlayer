#include <iostream>

#include "Font.hpp"

Font::Font(const char* xml_path, const char* image_path)
{
    load(xml_path, image_path);
}

Font::~Font()
{
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
