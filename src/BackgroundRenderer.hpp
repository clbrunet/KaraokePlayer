#pragma once

#include <vector>

#include "Program.hpp"
#include "math/Vec3.hpp"

class Karaoke;

#define NOISE_Y_OFFSET_NORMAL_SPEED 0.4f
#define NOISE_Y_OFFSET_ACCELERATION 1.0f

#define BACKGROUND_INDICES_COUNT 6

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

    void update(const Karaoke& karaoke, float running_time, float delta_time);
    void render(float aspect_ratio, const Karaoke& karaoke,
            float audio_length, float running_time) const;

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;
    float m_noise_y_offset_speed = 0.0f;
    float m_noise_y_offset = 0.0f;

    void initialize_OpenGL_objects();

    struct BackgroundVertex
    {
        Vec3 position;

        BackgroundVertex(Vec3 position);
    };
};
