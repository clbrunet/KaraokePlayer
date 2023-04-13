#ifndef KARAOKE_LINE_HPP
#define KARAOKE_LINE_HPP

#include <vector>

#include "karaoke/Word.hpp"

class Line
{
public:
    Line() = delete;
    Line(Line &&) = default;
    Line(const Line &) = default;
    Line &operator=(Line &&) = default;
    Line &operator=(const Line &) = default;
    ~Line() = default;

    Line(const pugi::xml_node& line_node, const Font& font);

    void set_models(float position);

    const std::vector<Word>& words() const;
    int letters_count() const;
    const Mat4& model() const;
    float get_end_ms() const;

private:
    std::vector<Word> m_words;
    Mat4 m_model;
};

#endif
