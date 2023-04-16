#include <iostream>

#include <glad/gl.h>

#include "rendering/PauseLoadingBarRenderer.hpp"
#include "math/Vec4.hpp"
#include "Application.hpp"

PauseLoadingBarRenderer::~PauseLoadingBarRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool PauseLoadingBarRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/pause_loading_bar.vert", "shaders/pause_loading_bar.frag"))
    {
        return false;
    }
    m_program.use();
    m_program.set_uniform_vec4("past_fragment_color", Vec4(1.0f, 0.6f, 0.0f, 1.0f));
    m_program.set_uniform_vec4("old_past_fragment_color", Vec4(1.0f, 0.9f, 0.0f, 1.0f));
    return true;
}

void PauseLoadingBarRenderer::render(const Application& application) const
{
    const Page* page = application.current_page();
    if (page == nullptr || page->lines().size() != 0)
    {
        return;
    }
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_mat4("model", application.scale());
    m_program.set_uniform_mat4("projection", application.projection());
    m_program.set_uniform_float("start_timing", page->start_timing());
    m_program.set_uniform_float("end_timing", page->end_timing());
    m_program.set_uniform_float("running_time", application.running_time());
    glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

void PauseLoadingBarRenderer::initialize_OpenGL_objects()
{
    Vertex m_vertices[] =
    {
        Vertex(Vec3(-LOADING_BAR_WIDTH_2, -LOADING_BAR_HEIGHT_2, 0.0f), Vec2(0.0f, 0.0f)),
        Vertex(Vec3(-LOADING_BAR_WIDTH_2, LOADING_BAR_HEIGHT_2,  0.0f), Vec2(0.0f, 1.0f)),
        Vertex(Vec3(LOADING_BAR_WIDTH_2,  LOADING_BAR_HEIGHT_2,  0.0f), Vec2(1.0f, 1.0f)),
        Vertex(Vec3(LOADING_BAR_WIDTH_2,  -LOADING_BAR_HEIGHT_2, 0.0f), Vec2(1.0f, 0.0f)),
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

PauseLoadingBarRenderer::Vertex::Vertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
