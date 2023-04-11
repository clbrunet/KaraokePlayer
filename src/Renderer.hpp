#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Font.hpp"
#include "Program.hpp"

class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer &&) = default;
    Renderer(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = default;
    Renderer &operator=(const Renderer &) = delete;
    ~Renderer();

    bool initialize();
    void render() const;

private:
    Font m_font = Font();
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    float m_vertices[30] =
    {
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
        -0.5f, 0.5f,  0.0f,    0.0f, 1.0f,
        0.5f,  0.5f,  0.0f,    1.0f, 1.0f,
        0.5f,  0.5f,  0.0f,    1.0f, 1.0f,
        0.5f, -0.5f,  0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
    };
    Program m_program = Program();
};

#endif
