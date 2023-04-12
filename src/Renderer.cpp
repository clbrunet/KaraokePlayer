#include <glad/gl.h>

#include "Letter.hpp"
#include "Renderer.hpp"
#include "Vec2.hpp"
#include "Mat4.hpp"

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
}

bool Renderer::initialize()
{
    glClearColor(0.3f, 0.1f, 0.7f, 1.0f);

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    if (!m_program.initialize("shaders/karaoke.vert", "shaders/karaoke.frag"))
    {
        return false;
    }
    m_program.use();
    m_program.set_uniform_int("sampler", 0);
    return true;
}

void Renderer::render(const Font& font, const std::vector<Letter>& letters)
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.image().texture());
    glBindVertexArray(m_vertex_array);
    for (const Letter& letter : letters)
    {
        m_program.set_uniform_vec2("char_texture_bottom_left", letter.bottom_left());
        m_program.set_uniform_vec2("char_texture_top_right", letter.top_right());
        m_program.set_uniform_mat4("model", letter.model());
        glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertices) / sizeof(float));
    }
}
