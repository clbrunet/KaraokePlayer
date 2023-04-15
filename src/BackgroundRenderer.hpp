#pragma once

#include <vector>

#include "Program.hpp"

#define NOISE_Y_OFFSET_NORMAL_SPEED 0.4f
#define NOISE_Y_OFFSET_START_SPEED_UP_DURATION 1.0f

class BackgroundRenderer
{
public:
    BackgroundRenderer() = default;
    BackgroundRenderer(BackgroundRenderer &&) = delete;
    BackgroundRenderer(const BackgroundRenderer &) = delete;
    BackgroundRenderer &operator=(BackgroundRenderer &&) = delete;
    BackgroundRenderer &operator=(const BackgroundRenderer &) = delete;
    ~BackgroundRenderer();

    bool initialize();

    void update(float first_syllabe_start_timing,
            float running_time, float delta_time);
    void render(float aspect_ratio, float first_syllabe_start_timing, float running_time) const;

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;
    float m_noise_y_offset_speed = 0.0f;
    float m_noise_y_offset = 0.0f;

    void initialize_OpenGL_objects();
};
