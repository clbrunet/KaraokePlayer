#ifndef SONG_HPP
#define SONG_HPP

#include <vector>

#include <pugixml.hpp>

#include "karaoke/Page.hpp"

class Song
{
public:
    Song() = default;
    Song(Song &&) = default;
    Song(const Song &) = delete;
    Song &operator=(Song &&) = default;
    Song &operator=(const Song &) = delete;
    ~Song() = default;

    Song(const char* ogg_path, const char* xml_path, const Font& font);

    bool load(const char* xml_path, const char* ogg_path, const Font& font);

    const std::vector<Page>& pages() const;

private:
    std::vector<Page> m_pages;
};

#endif
