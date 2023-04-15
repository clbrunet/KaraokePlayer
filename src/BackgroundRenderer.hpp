#pragma once

#include <vector>

#include "Program.hpp"

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
    void initialize_OpenGL_objects();
    void render(float first_syllabe_start_timing, float running_time) const;

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;
};
