#include <iostream>

#include <glad/gl.h>

#include "rendering/PlusMinusButtonsRenderer.hpp"
#include "graphics/PlusMinusButton.hpp"
#include "math/Vec4.hpp"
#include "Application.hpp"

PlusMinusButtonsRenderer::~PlusMinusButtonsRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool PlusMinusButtonsRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/plus_minus_button.vert", "shaders/plus_minus_button.frag"))
    {
        return false;
    }
    m_program.use();
    m_program.set_uniform_float("clicked_timer_duration", PlusMinusButton::CLICKED_TIMER_DURATION);
    return true;
}

void PlusMinusButtonsRenderer::render(const Application& application) const
{
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_float("aspect_ratio", application.aspect_ratio());
    for (const PlusMinusButton& plus_minus_button : application.plus_minus_buttons())
    {
        m_program.set_uniform_mat4("model", plus_minus_button.model());
        m_program.set_uniform_bool("is_minus", plus_minus_button.is_minus());
        m_program.set_uniform_float("clicked_timer", plus_minus_button.clicked_timer());
        glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, 0);
    }
}

void PlusMinusButtonsRenderer::initialize_OpenGL_objects()
{
    Vertex m_vertices[] =
    {
        Vertex(Vec3(-PLUS_MINUS_BUTTON_WIDTH_2, -PLUS_MINUS_BUTTON_HEIGHT_2, 0.0f),
                Vec2(0.0f, 0.0f)),
        Vertex(Vec3(-PLUS_MINUS_BUTTON_WIDTH_2, PLUS_MINUS_BUTTON_HEIGHT_2,  0.0f),
                Vec2(0.0f, 1.0f)),
        Vertex(Vec3(PLUS_MINUS_BUTTON_WIDTH_2,  PLUS_MINUS_BUTTON_HEIGHT_2,  0.0f),
                Vec2(1.0f, 1.0f)),
        Vertex(Vec3(PLUS_MINUS_BUTTON_WIDTH_2,  -PLUS_MINUS_BUTTON_HEIGHT_2, 0.0f),
                Vec2(1.0f, 0.0f)),
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

PlusMinusButtonsRenderer::Vertex::Vertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
