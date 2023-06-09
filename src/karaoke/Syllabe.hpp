#pragma once

#include <cstdint>
#include <vector>

#include "karaoke/Letter.hpp"

class Syllabe
{
public:
    Syllabe() = delete;
    Syllabe(Syllabe &&) = default;
    Syllabe(const Syllabe &) = default;
    Syllabe &operator=(Syllabe &&) = default;
    Syllabe &operator=(const Syllabe &) = default;
    ~Syllabe() = default;

    Syllabe(const pugi::xml_node& syllabe_node, const Font& font);

    void set_models(float local_position);
    void set_timings();

    const std::vector<Letter>& letters() const;
    int letters_count() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;
    float get_speech_rate() const;

private:
    float m_start_timing = 0.0f;
    float m_end_timing = 0.0f;
    std::vector<Letter> m_letters;
    Mat4 m_model = Mat4::identity();

    static uint64_t parse_ms_text(const std::string& text);
};
