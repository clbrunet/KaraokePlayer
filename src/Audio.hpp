#pragma once

#include <cstdint>

class Audio
{
public:
    Audio() = default;
    Audio(Audio &&) = default;
    Audio(const Audio &) = default;
    Audio &operator=(Audio &&) = default;
    Audio &operator=(const Audio &) = default;
    ~Audio();

    bool load(const char* ogg_path, uint32_t audio_end_event);

    struct CallbackData
    {
        int audio_length = -1;
        uint8_t* audio_position = nullptr;
        uint32_t audio_end_event = -1;
    };

private:
    short* m_ogg_output = nullptr;
    CallbackData m_callback_data;
};
