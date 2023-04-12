#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

#include "Font.hpp"
#include "Program.hpp"

class Letter;

#define LETTERS_SCALE_FACTOR 2.0f

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
    void render(const Font& font, const std::vector<Letter>& letters);

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    float m_vertices[30] =
    {
        -0.02f, -0.07f, 0.0f,    0.0f, 0.0f,
        -0.02f, 0.07f,  0.0f,    0.0f, 1.0f,
        0.02f,  0.07f,  0.0f,    1.0f, 1.0f,
        0.02f,  0.07f,  0.0f,    1.0f, 1.0f,
        0.02f,  -0.07f, 0.0f,    1.0f, 0.0f,
        -0.02f, -0.07f, 0.0f,    0.0f, 0.0f,
    };
    Program m_program = Program();
};

#endif
