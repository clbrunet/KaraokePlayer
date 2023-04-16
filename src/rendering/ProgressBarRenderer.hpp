#pragma once

#include "Program.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

class Application;
class Page;

class ProgressBarRenderer
{
public:
    ProgressBarRenderer() = default;
    ProgressBarRenderer(ProgressBarRenderer &&) = delete;
    ProgressBarRenderer(const ProgressBarRenderer &) = delete;
    ProgressBarRenderer &operator=(ProgressBarRenderer &&) = delete;
    ProgressBarRenderer &operator=(const ProgressBarRenderer &) = delete;
    ~ProgressBarRenderer();

    bool initialize(float audio_length);

    void render(const Application& application) const;

    static constexpr float PROGRESS_BAR_HEIGHT = 0.05f;
    static constexpr float PROGRESS_BAR_HEIGHT_2 = PROGRESS_BAR_HEIGHT / 2.0f;

private:
    static constexpr int INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;

    void initialize_OpenGL_objects();

    struct Vertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        Vertex(Vec3 position, Vec2 uvs);
    };
};
