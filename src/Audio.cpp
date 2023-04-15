#include <iostream>

#include <SDL.h>
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#include "Audio.hpp"

Audio::~Audio()
{
    SDL_CloseAudio();
    free(m_ogg_output);
}

static void audio_callback(void* userdata, uint8_t* stream, int len) {
    Audio::CallbackData* audio_callback_data = (Audio::CallbackData*)userdata;
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

float Audio::load(const char* ogg_path, uint32_t audio_end_event)
{
    int channels;
    int sample_rate;
    int length = stb_vorbis_decode_filename(ogg_path, &channels, &sample_rate, &m_ogg_output);
    if (length < 0)
    {
        return -1.0f;
    }
    m_callback_data.audio_length = length * channels * (sizeof(int16_t) / sizeof(int8_t));
    m_callback_data.audio_position = (uint8_t*)m_ogg_output;
    m_callback_data.audio_end_event = audio_end_event;

    SDL_AudioSpec spec;
    spec.freq = sample_rate;
    spec.format = AUDIO_S16;
    spec.channels = channels;
    spec.samples = 2048;
    spec.callback = audio_callback;
    spec.userdata = &m_callback_data;
    if (SDL_OpenAudio(&spec, nullptr) < 0) {
        std::cerr << "Coundl't open audio device." << std::endl;
        return -1.0f;
    }
    return (float)length / (float)sample_rate;
}
