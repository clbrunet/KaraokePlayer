#ifndef SONG_HPP
#define SONG_HPP

#include <pugixml.hpp>

class Song
{
public:
    Song() = default;
    Song(Song &&) = default;
    Song(const Song &) = delete;
    Song &operator=(Song &&) = default;
    Song &operator=(const Song &) = delete;
    ~Song() = default;

    Song(const char* ogg_path, const char* xml_path);

    bool load(const char* xml_path, const char* ogg_path);

private:
    pugi::xml_document m_doc;
};

#endif
