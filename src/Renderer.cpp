#include <iostream>

#include <glad/gl.h>

#include "Renderer.hpp"
#include "math/Vec2.hpp"
#include "math/Vec4.hpp"
#include "math/Mat4.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Page.hpp"
#include "karaoke/Syllabe.hpp"
#include "karaoke/Word.hpp"

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
    m_program.set_uniform_vec4("already_sung_text_color", Vec4(1.0f, 0.6f, 0.0f, 1.0f));
    return true;
}

void Renderer::render(const Font& font, const Page* page, float running_time,
        const Mat4& projection, const Mat4& font_scale) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (page == nullptr)
    {
        return;
    }
    m_program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.image().texture());
    glBindVertexArray(m_vertex_array);
    m_program.set_uniform_float("running_time", running_time);
    m_program.set_uniform_mat4("projection", projection);
    render_page(*page, font_scale);
}

void Renderer::render_page(const Page& page, const Mat4& font_scale) const
{
    for (const Line& line : page.lines())
    {
        render_line(line, font_scale);
    }
}

void Renderer::render_line(const Line& line, const Mat4& font_scale) const
{
    for (const Word& word : line.words())
    {
        render_word(word, font_scale * line.model());
    }
}

void Renderer::render_word(const Word& word, const Mat4& line_model) const
{
    for (const Syllabe& syllabe : word.syllabes())
    {
        render_syllabe(syllabe, line_model * word.model());
    }
}

void Renderer::render_syllabe(const Syllabe& syllabe, const Mat4& word_model) const
{
    for (const Letter& letter : syllabe.letters())
    {
        render_letter(letter, word_model * syllabe.model());
    }
}

void Renderer::render_letter(const Letter& letter, const Mat4& syllabe_model) const
{
    m_program.set_uniform_vec2("char_texture_bottom_left", letter.texture_bottom_left());
    m_program.set_uniform_vec2("char_texture_top_right", letter.texture_top_right());
    m_program.set_uniform_mat4("model", syllabe_model * letter.model());
    m_program.set_uniform_float("letter_start_timing", letter.start_timing());
    m_program.set_uniform_float("letter_end_timing", letter.end_timing());
    glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertices) / sizeof(float));
}
