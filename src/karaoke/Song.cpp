#include <iostream>

#include "karaoke/Song.hpp"

Song::Song(const char* ogg_path, const char* xml_path, const Font& font)
{
    load(ogg_path, xml_path, font);
}

bool Song::load(const char* xml_path, const char* ogg_path, const Font& font)
{
    pugi::xml_document doc;
    if (!doc.load_file(xml_path))
    {
        std::cerr << "Coundl't load the song xml '" << xml_path << "'" << std::endl;
        return false;
    }
    for (pugi::xml_node page_node : doc.child("karaoke"))
    {
        m_pages.push_back(Page(page_node, font));
    }
    for (Page& page : m_pages)
    {
        page.set_models();
    }
    return true;
}

const std::vector<Page>& Song::pages() const
{
    return m_pages;
}
