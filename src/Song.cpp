#include <iostream>

#include "Song.hpp"

Song::Song(const char* ogg_path, const char* xml_path)
{
    load(ogg_path, xml_path);
}

bool Song::load(const char* xml_path, const char* ogg_path)
{
    if (!m_doc.load_file(xml_path))
    {
        std::cerr << "Coundl't load the song xml '" << xml_path << "'" << std::endl;
        return false;
    }
    return true;
}
