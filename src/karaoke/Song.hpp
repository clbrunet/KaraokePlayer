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
    ~Song();

    Song(const char* ogg_path, const char* xml_path, const Font& font);

    bool load(const char* xml_path, const char* ogg_path, const Font& font);

    const std::vector<Page>& pages() const;

    struct AudioCallbackData
    {
        int audio_length = -1;
        uint8_t* audio_position = nullptr;
    };

private:
    std::vector<Page> m_pages;
    short* m_ogg_output = nullptr;
    AudioCallbackData m_audio_callback_data;

    bool load_xml(const char* xml_path, const Font& font);
    bool load_audio(const char* ogg_path);
};

#endif
