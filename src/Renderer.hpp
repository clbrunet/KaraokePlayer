#pragma once

#include <vector>

#include "graphics/Font.hpp"
#include "Program.hpp"
#include "math/Vec3.hpp"

class Page;
class Line;
class Word;
class Syllabe;
class Letter;

#define LETTER_BASE_WIDTH 0.01f
#define LETTER_BASE_HEIGHT 0.035f
#define WORDS_SPACING_BASE_WIDTH (LETTER_BASE_WIDTH / 1.5f)
#define LINES_SPACING_BASE_HEIGHT (LETTER_BASE_HEIGHT * 0.0f)

#define LETTER_INDICES_COUNT 6

class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer &&) = delete;
    Renderer(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = delete;
    Renderer &operator=(const Renderer &) = delete;
    ~Renderer();

    bool initialize();
    void render(const Font& font, const Page* page, float running_time,
            const Mat4& projection, const Mat4& font_scale) const;

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_letter_program;
    Program m_loading_bar_program;

    void initialize_OpenGL_objects();

    void render_loading_bar(const Page& page) const;
    void render_page(const Page& page, const Mat4& font_scale) const;
    void render_line(const Line& line, const Mat4& page_model, const Mat4& font_scale) const;
    void render_word(const Word& word, const Mat4& line_model) const;
    void render_syllabe(const Syllabe& syllabe, const Mat4& word_model) const;
    void render_letter(const Letter& letter, const Mat4& syllabe_model) const;

    struct LetterVertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        LetterVertex(Vec3 position, Vec2 uvs);
    };
};
