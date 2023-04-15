#pragma once

#include "Program.hpp"
#include "math/Mat4.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

class Application;
class Page;
class Line;
class Word;
class Syllabe;
class Letter;

class PageRenderer
{
public:
    PageRenderer() = default;
    PageRenderer(PageRenderer &&) = delete;
    PageRenderer(const PageRenderer &) = delete;
    PageRenderer &operator=(PageRenderer &&) = delete;
    PageRenderer &operator=(const PageRenderer &) = delete;
    ~PageRenderer();

    bool initialize();

    void render(const Application& application) const;

    static constexpr float LETTER_BASE_WIDTH = 0.01f;
    static constexpr float LETTER_BASE_WIDTH_2 = LETTER_BASE_WIDTH / 2.0f;
    static constexpr float LETTER_BASE_HEIGHT = 0.035f;
    static constexpr float LETTER_BASE_HEIGHT_2 = LETTER_BASE_HEIGHT / 2.0f;
    static constexpr float WORDS_SPACING_BASE_WIDTH = LETTER_BASE_WIDTH / 1.5f;
    static constexpr float LINES_SPACING_BASE_HEIGHT = LETTER_BASE_HEIGHT * 0.0f;

private:
    static constexpr int LETTER_INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_letter_program;
    Mat4 m_font_scale = Mat4::identity();

    void initialize_OpenGL_objects();

    void render_page(const Page& page) const;
    void render_line(const Line& line, const Mat4& parent_model) const;
    void render_word(const Word& word, const Mat4& parent_model) const;
    void render_syllabe(const Syllabe& syllabe, const Mat4& parent_model) const;
    void render_letter(const Letter& letter, const Mat4& parent_model) const;

    struct LetterVertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        LetterVertex(Vec3 position, Vec2 uvs);
    };
};
