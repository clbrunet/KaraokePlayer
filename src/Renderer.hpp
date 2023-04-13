#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

#include "graphics/Font.hpp"
#include "Program.hpp"

class Page;
class Line;
class Word;
class Syllabe;
class Letter;

#define LETTER_BASE_WIDTH 0.01f
#define LETTER_BASE_HEIGHT 0.035f
#define SPACE_BASE_WIDTH (LETTER_BASE_WIDTH / 1.5f)

class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer &&) = default;
    Renderer(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = default;
    Renderer &operator=(const Renderer &) = delete;
    ~Renderer();

    bool initialize();
    void initialize_OpenGL_objects();
    void render(const Font& font, const Page* page, float running_time,
            const Mat4& projection , const Mat4& font_scale) const;

private:
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program = Program();

    void render_page(const Page& page, const Mat4& font_scale) const;
    void render_line(const Line& line, const Mat4& font_scale) const;
    void render_word(const Word& word, const Mat4& line_model) const;
    void render_syllabe(const Syllabe& syllabe, const Mat4& word_model) const;
    void render_letter(const Letter& letter, const Mat4& syllabe_model) const;
};

#endif
