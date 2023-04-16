#include <iostream>

#include <glad/gl.h>

#include "rendering/ProgressBarRenderer.hpp"
#include "math/Vec4.hpp"
#include "Application.hpp"

ProgressBarRenderer::~ProgressBarRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool ProgressBarRenderer::initialize(float audio_length)
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/progress_bar.vert", "shaders/progress_bar.frag"))
    {
        return false;
    }
    m_program.use();
    m_program.set_uniform_vec4("past_fragment_color", Vec4(0.8f, 0.0f, 0.0f, 1.0f));
    m_program.set_uniform_float("audio_length", audio_length);
    return true;
}

void ProgressBarRenderer::render(const Application& application) const
{
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_float("running_time", application.running_time());
    glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

void ProgressBarRenderer::initialize_OpenGL_objects()
{
    Vertex m_vertices[] =
    {
        Vertex(Vec3(-1.0f, -1.0f,                       0.0f), Vec2(0.0f, 0.0f)),
        Vertex(Vec3(-1.0f, -1.0f + PROGRESS_BAR_HEIGHT, 0.0f), Vec2(0.0f, 1.0f)),
        Vertex(Vec3(1.0f,  -1.0f + PROGRESS_BAR_HEIGHT, 0.0f), Vec2(1.0f, 1.0f)),
        Vertex(Vec3(1.0f,  -1.0f,                       0.0f), Vec2(1.0f, 0.0f)),
    };
    unsigned int m_indices[INDICES_COUNT] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(Vertex::uvs) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, uvs));
    glEnableVertexAttribArray(1);
}

ProgressBarRenderer::Vertex::Vertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
