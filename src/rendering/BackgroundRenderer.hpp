#pragma once

#include "Program.hpp"
#include "math/Vec3.hpp"

class Karaoke;
class Application;

class BackgroundRenderer
{
public:
    BackgroundRenderer() = default;
    BackgroundRenderer(BackgroundRenderer &&) = delete;
    BackgroundRenderer(const BackgroundRenderer &) = delete;
    BackgroundRenderer &operator=(BackgroundRenderer &&) = delete;
    BackgroundRenderer &operator=(const BackgroundRenderer &) = delete;
    ~BackgroundRenderer();

    bool initialize(const Karaoke& karaoke, float audio_length);

    void update(const Application& application, float delta_time);
    void render(const Application& application) const;

private:

    static constexpr float NOISE_Y_OFFSET_NORMAL_SPEED = 0.4f;
    static constexpr float NOISE_Y_OFFSET_MAX_ACCELERATION = 1.0f;
    static constexpr int INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;
    float m_noise_y_offset_speed = 0.0f;
    float m_noise_y_offset = 0.0f;

    void initialize_OpenGL_objects();

    struct Vertex
    {
        Vec3 position;

        Vertex(Vec3 position);
    };
};
