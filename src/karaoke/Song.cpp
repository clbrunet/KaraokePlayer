#include <algorithm>
#include <cstdint>
#include <iostream>

#include <SDL.h>
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#include "karaoke/Song.hpp"

Song::Song(const char* xml_path, const Font& font, const char* ogg_path, uint32_t audio_end_event)
{
    load(xml_path, font, ogg_path, audio_end_event);
}

Song::~Song()
{
    SDL_CloseAudio();
    free(m_ogg_output);
}

bool Song::load(const char* xml_path, const Font& font,
        const char* ogg_path, uint32_t audio_end_event)
{
    if (!load_xml(xml_path, font))
    {
        return false;
    }
    add_empty_pages();
    if (!load_audio(ogg_path, audio_end_event))
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
        page.set_models(Vec2::zero());
        page.set_timings();
    }
    return true;
}

void Song::add_empty_pages()
{
    constexpr float PAGES_TIMINGS_DIFF_MINIMUM = 5.0f;
    constexpr float EMPTY_PAGE_TO_NEXT_DIFF = 2.0f;
    static_assert(PAGES_TIMINGS_DIFF_MINIMUM > EMPTY_PAGE_TO_NEXT_DIFF,
            "A minimum page timings difference greater than"
            "the created differences will cause an infinite loop");
    float last_end_timing = 0.0f;
    for (size_t i = 0; i < m_pages.size(); i++) {
        float start_timing = m_pages[i].start_timing();
        float end_timing = m_pages[i].end_timing();
        if (start_timing - last_end_timing > PAGES_TIMINGS_DIFF_MINIMUM)
        {
            m_pages.insert(m_pages.begin() + i,
                    Page(last_end_timing, start_timing - EMPTY_PAGE_TO_NEXT_DIFF));
            i++;
        }
        last_end_timing = end_timing;
    }
}

static void audio_callback(void* userdata, uint8_t* stream, int len) {
    Song::AudioCallbackData* audio_callback_data = (Song::AudioCallbackData*)userdata;
    SDL_memset(stream, 0, len); // silence the stream
    if (audio_callback_data->audio_length == 0)
    {
        SDL_Event event;
        event.type = audio_callback_data->audio_end_event;
        SDL_PushEvent(&event);
        return;
    }
    len = std::min(len, audio_callback_data->audio_length);
    SDL_MixAudio(stream, audio_callback_data->audio_position, len, SDL_MIX_MAXVOLUME);
    audio_callback_data->audio_position += len;
    audio_callback_data->audio_length -= len;
}

bool Song::load_audio(const char* ogg_path, uint32_t audio_end_event)
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
    m_audio_callback_data.audio_end_event = audio_end_event;

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
    return true;
}

const std::vector<Page>& Song::pages() const
{
    return m_pages;
}
