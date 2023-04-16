#include <iostream>

#include <glad/gl.h>

#include "rendering/PageRenderer.hpp"
#include "Application.hpp"
#include "math/Vec2.hpp"
#include "math/Vec4.hpp"
#include "math/Mat4.hpp"
#include "karaoke/Page.hpp"
#include "karaoke/Word.hpp"
#include "karaoke/Syllabe.hpp"
#include "karaoke/Letter.hpp"

PageRenderer::~PageRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool PageRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_letter_program.initialize("shaders/letter.vert", "shaders/letter.frag"))
    {
        return false;
    }
    m_letter_program.use();
    m_letter_program.set_uniform_int("sampler", 0);
    m_letter_program.set_uniform_vec4("past_fragment_color", Vec4(1.0f, 0.6f, 0.0f, 1.0f));
    m_letter_program.set_uniform_vec4("old_past_fragment_color", Vec4(1.0f, 0.9f, 0.0f, 1.0f));
    return true;
}

void PageRenderer::render(const Application& application) const
{
    const Page* page = application.current_page();
    if (page == nullptr || page->lines().size() == 0)
    {
        return;
    }
    glBindVertexArray(m_vertex_array);
    m_letter_program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, application.font().image().texture());
    m_letter_program.set_uniform_float("running_time", application.running_time());
    m_letter_program.set_uniform_mat4("projection", application.projection());
    render_page(*page, application.scale());
}

void PageRenderer::initialize_OpenGL_objects()
{
    LetterVertex m_letter_vertices[] =
    {
        LetterVertex(Vec3(-LETTER_BASE_WIDTH_2, -LETTER_BASE_HEIGHT_2, 0.0f), Vec2(0.0f, 0.0f)),
        LetterVertex(Vec3(-LETTER_BASE_WIDTH_2, LETTER_BASE_HEIGHT_2, 0.0f), Vec2(0.0f, 1.0f)),
        LetterVertex(Vec3(LETTER_BASE_WIDTH_2, LETTER_BASE_HEIGHT_2, 0.0f), Vec2(1.0f, 1.0f)),
        LetterVertex(Vec3(LETTER_BASE_WIDTH_2, -LETTER_BASE_HEIGHT_2, 0.0f), Vec2(1.0f, 0.0f)),
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_letter_vertices), m_letter_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_letter_indices), m_letter_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(LetterVertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(LetterVertex), (void*)offsetof(LetterVertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(LetterVertex::uvs) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(LetterVertex), (void*)offsetof(LetterVertex, uvs));
    glEnableVertexAttribArray(1);
}

void PageRenderer::render_page(const Page& page, const Mat4& scale) const
{
    for (const Line& line : page.lines())
    {
        render_line(line, page.model() * scale);
    }
}

void PageRenderer::render_line(const Line& line, const Mat4& parent_model) const
{
    for (const Word& word : line.words())
    {
        render_word(word, parent_model * line.model());
    }
}

void PageRenderer::render_word(const Word& word, const Mat4& parent_model) const
{
    for (const Syllabe& syllabe : word.syllabes())
    {
        render_syllabe(syllabe, parent_model * word.model());
    }
}

void PageRenderer::render_syllabe(const Syllabe& syllabe, const Mat4& parent_model) const
{
    for (const Letter& letter : syllabe.letters())
    {
        render_letter(letter, parent_model * syllabe.model());
    }
}

void PageRenderer::render_letter(const Letter& letter, const Mat4& parent_model) const
{
    m_letter_program.set_uniform_vec2("char_texture_bottom_left",
            letter.texture_coordinates_bottom_left());
    m_letter_program.set_uniform_vec2("char_texture_top_right",
            letter.texture_coordinates_top_right());
    m_letter_program.set_uniform_mat4("model", parent_model * letter.model());
    m_letter_program.set_uniform_float("letter_start_timing", letter.start_timing());
    m_letter_program.set_uniform_float("letter_end_timing", letter.end_timing());
    glDrawElements(GL_TRIANGLES, LETTER_INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

PageRenderer::LetterVertex::LetterVertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
