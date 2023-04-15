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
    glDeleteBuffers(1, &m_element_buffer);
}

bool Renderer::initialize()
{
    initialize_OpenGL_objects();
    Vec4 already_sung_text_color(1.0f, 0.6f, 0.0f, 1.0f);
    Vec4 old_already_sung_text_color(1.0f, 0.9f, 0.0f, 1.0f);
    if (!m_letter_program.initialize("shaders/karaoke.vert", "shaders/karaoke.frag"))
    {
        return false;
    }
    m_letter_program.use();
    m_letter_program.set_uniform_int("sampler", 0);
    m_letter_program.set_uniform_vec4("already_sung_text_color", already_sung_text_color);
    m_letter_program.set_uniform_vec4("old_already_sung_text_color", old_already_sung_text_color);
    if (!m_loading_bar_program.initialize("shaders/loading_bar.vert", "shaders/loading_bar.frag"))
    {
        return false;
    }
    m_loading_bar_program.use();
    m_loading_bar_program.set_uniform_vec4("already_sung_text_color", already_sung_text_color);
    m_loading_bar_program.set_uniform_vec4("old_already_sung_text_color",
            old_already_sung_text_color);
    return true;
}

void Renderer::render(const Font& font, const Page* page, float running_time,
        const Mat4& projection, const Mat4& font_scale) const
{
    if (page == nullptr)
    {
        return;
    }
    const Program* program;
    if (page->lines().size() == 0)
    {
        program = &m_loading_bar_program;
    }
    else
    {
        program = &m_letter_program;
    }
    glBindVertexArray(m_vertex_array);
    program->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font.image().texture());
    program->set_uniform_float("running_time", running_time);
    program->set_uniform_mat4("projection", projection);
    if (page->lines().size() == 0)
    {
        render_loading_bar(*page);
    }
    else
    {
        render_page(*page, font_scale);
    }
}

void Renderer::initialize_OpenGL_objects()
{
    LetterVertex m_letter_vertices[] =
    {
        LetterVertex(Vec3(-(LETTER_BASE_WIDTH / 2.0f), -(LETTER_BASE_HEIGHT / 2.0f), 0.0f),
                Vec2(0.0f, 0.0f)),
        LetterVertex(Vec3(-(LETTER_BASE_WIDTH / 2.0f), (LETTER_BASE_HEIGHT / 2.0f), 0.0f),
                Vec2(0.0f, 1.0f)),
        LetterVertex(Vec3((LETTER_BASE_WIDTH / 2.0f), (LETTER_BASE_HEIGHT / 2.0f), 0.0f),
                Vec2(1.0f, 1.0f)),
        LetterVertex(Vec3((LETTER_BASE_WIDTH / 2.0f), -(LETTER_BASE_HEIGHT / 2.0f), 0.0f),
                Vec2(1.0f, 0.0f)),
    };
    unsigned int m_letter_indices[LETTER_INDICES_COUNT] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_letter_vertices),
            m_letter_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_letter_indices),
            m_letter_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(LetterVertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(LetterVertex), (void*)offsetof(LetterVertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(LetterVertex::uvs) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(LetterVertex), (void*)offsetof(LetterVertex, uvs));
    glEnableVertexAttribArray(1);
}

void Renderer::render_loading_bar(const Page& page) const
{
    m_loading_bar_program.set_uniform_mat4("scale", Mat4::identity().scale(200.0f, 5.0f, 1.0f));
    m_loading_bar_program.set_uniform_float("start_timing", page.start_timing());
    m_loading_bar_program.set_uniform_float("end_timing", page.end_timing());
    glDrawElements(GL_TRIANGLES, LETTER_INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

void Renderer::render_page(const Page& page, const Mat4& font_scale) const
{
    for (const Line& line : page.lines())
    {
        render_line(line, page.model(), font_scale);
    }
}

void Renderer::render_line(const Line& line, const Mat4& page_model, const Mat4& font_scale) const
{
    for (const Word& word : line.words())
    {
        render_word(word, page_model * font_scale * line.model());
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
    m_letter_program.set_uniform_vec2("char_texture_bottom_left",
            letter.texture_coordinates_bottom_left());
    m_letter_program.set_uniform_vec2("char_texture_top_right",
            letter.texture_coordinates_top_right());
    m_letter_program.set_uniform_mat4("model", syllabe_model * letter.model());
    m_letter_program.set_uniform_float("letter_start_timing", letter.start_timing());
    m_letter_program.set_uniform_float("letter_end_timing", letter.end_timing());
    glDrawElements(GL_TRIANGLES, LETTER_INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

Renderer::LetterVertex::LetterVertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
