#pragma once

#include <vector>

#include "karaoke/Syllabe.hpp"

class Word
{
public:
    Word() = delete;
    Word(Word &&) = default;
    Word(const Word &) = default;
    Word &operator=(Word &&) = default;
    Word &operator=(const Word &) = default;
    ~Word() = default;

    Word(const pugi::xml_node& word_node, const Font& font);

    void set_models(float local_position);
    void set_timings();

    const std::vector<Syllabe>& syllabes() const;
    int letters_count() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;
    float get_speech_rate(float running_time) const;

private:
    std::vector<Syllabe> m_syllabes;
    Mat4 m_model = Mat4::identity();
    float m_start_timing = 0.0f;
    float m_end_timing = 0.0f;
};
