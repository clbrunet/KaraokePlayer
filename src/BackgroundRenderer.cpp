#include <iostream>

#include <glad/gl.h>

#include "BackgroundRenderer.hpp"
#include "math/Vec2.hpp"
#include "math/Vec4.hpp"
#include "math/Mat4.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Page.hpp"
#include "karaoke/Syllabe.hpp"
#include "karaoke/Word.hpp"

BackgroundRenderer::~BackgroundRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool BackgroundRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/background.vert", "shaders/background.frag"))
    {
        return false;
    }
    m_program.use();
    return true;
}

void BackgroundRenderer::initialize_OpenGL_objects()
{
    float m_background_vertices[] =
    {
        // position
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  -1.0f, 0.0f,
    };
    unsigned int m_background_indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_background_vertices),
            m_background_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_background_indices),
            m_background_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void BackgroundRenderer::render(float first_syllabe_start_timing, float running_time) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_float("first_syllabe_start_timing", first_syllabe_start_timing);
    m_program.set_uniform_float("running_time", running_time);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
