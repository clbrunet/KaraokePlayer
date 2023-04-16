#pragma once

#include "SDL_audio.h"

#include <cstdint>

class Audio
{
public:
    Audio() = default;
    Audio(Audio &&) = delete;
    Audio(const Audio &) = delete;
    Audio &operator=(Audio &&) = delete;
    Audio &operator=(const Audio &) = delete;
    ~Audio();

    // return the audio length in seconds or -1.0f on errors
    float load(const char* ogg_path, uint32_t audio_end_event);

    void turn_down_volume();
    void turn_up_volume();

    struct CallbackData
    {
        int audio_length = -1;
        uint8_t* audio_position = nullptr;
        uint32_t audio_end_event = -1;
        int volume = SDL_MIX_MAXVOLUME;
    };

private:
    short* m_ogg_output = nullptr;
    CallbackData m_callback_data;
};
