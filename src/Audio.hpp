#pragma once

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
