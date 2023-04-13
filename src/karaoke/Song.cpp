#include <algorithm>
#include <cstdint>
#include <iostream>

#include <SDL.h>
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#include "karaoke/Song.hpp"

Song::Song(const char* ogg_path, const char* xml_path, const Font& font)
{
    load(ogg_path, xml_path, font);
}

Song::~Song()
{
    SDL_CloseAudio();
    free(m_ogg_output);
}

bool Song::load(const char* xml_path, const char* ogg_path, const Font& font)
{
    if (!load_xml(xml_path, font))
    {
        return false;
    }
    if (!load_audio(ogg_path))
    {
        return false;
    }
    return true;
}

bool Song::load_xml(const char* xml_path, const Font& font)
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

static void audio_callback(void* userdata, uint8_t* stream, int len) {
    Song::AudioCallbackData* audio_callback_data = (Song::AudioCallbackData*)userdata;
    SDL_memset(stream, 0, len); // silence the stream
    if (audio_callback_data->audio_length == 0)
    {
        return;
    }
    len = std::min(len, audio_callback_data->audio_length);
    SDL_MixAudio(stream, audio_callback_data->audio_position, len, SDL_MIX_MAXVOLUME);
    audio_callback_data->audio_position += len;
    audio_callback_data->audio_length -= len;
}

bool Song::load_audio(const char* ogg_path)
{
    int channels;
    int sample_rate;
    int length = stb_vorbis_decode_filename(ogg_path, &channels, &sample_rate, &m_ogg_output);
    if (length < 0)
    {
        return false;
    }
    m_audio_callback_data.audio_length = length * channels * (sizeof(int16_t) / sizeof(int8_t));
    m_audio_callback_data.audio_position = (uint8_t*)m_ogg_output;

    SDL_AudioSpec spec;
    spec.freq = sample_rate;
    spec.format = AUDIO_S16;
    spec.channels = channels;
    spec.samples = 2048;
    spec.callback = audio_callback;
    spec.userdata = &m_audio_callback_data;
    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        std::cerr << "Coundl't open audio device." << std::endl;
        return false;
    }
    SDL_PauseAudio(0);

    return true;
}

const std::vector<Page>& Song::pages() const
{
    return m_pages;
}
