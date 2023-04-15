#pragma once

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

    void set_models(float local_position);
    void set_timings();

    const std::vector<Word>& words() const;
    int letters_count() const;
    int spaces_count() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;
    float get_speech_rate(float running_time) const;

private:
    std::vector<Word> m_words;
    Mat4 m_model = Mat4::identity();
    float m_start_timing = 0.0f;
    float m_end_timing = 0.0f;
};
