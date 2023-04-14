#include <iostream>
#include <sstream>

#include "Renderer.hpp"
#include "karaoke/Syllabe.hpp"

Syllabe::Syllabe(const pugi::xml_node& syllabe_node, const Font& font) :
    m_model(Mat4::identity())
{
    m_start_second = (float)parse_ms_text(syllabe_node.child("start").text().get()) / 1000.0f;
    m_end_second = (float)parse_ms_text(syllabe_node.child("end").text().get()) / 1000.0f;

    const unsigned char* chars = (const unsigned char*)syllabe_node.child("text").text().get();
    while (*chars != '\0')
    {
        m_letters.push_back(Letter(font, *chars));
        chars++;
    }
}

void Syllabe::set_models(float local_position)
{
    m_model = Mat4::identity().translate(Vec2(local_position, 0.0f));

    // spread letter positions around 0
    float letters_width = (float)letters_count() * LETTER_BASE_WIDTH;
    float letter_local_position = (letters_width - LETTER_BASE_WIDTH) * -0.5f;
    for (Letter& letter : m_letters)
    {
        letter.set_model(letter_local_position);
        letter_local_position += LETTER_BASE_WIDTH;
    }
}

void Syllabe::set_timings()
{
    float timing = m_start_second;
    float letter_duration = (m_end_second - m_start_second) / letters_count();
    for (Letter& letter : m_letters)
    {
        letter.set_timings(timing, timing + letter_duration);
        timing += letter_duration;
    }
}

const std::vector<Letter>& Syllabe::letters() const
{
    return m_letters;
}

int Syllabe::letters_count() const
{
    return m_letters.size();
}

const Mat4& Syllabe::model() const
{
    return m_model;
}

float Syllabe::get_end_second() const
{
    return m_end_second;
}

uint64_t Syllabe::parse_ms_text(const std::string& text) const
{
    std::istringstream isstream(text);
    char separator = 0;
    uint64_t hours = -1;
    uint64_t minutes = -1;
    uint64_t seconds = -1;
    uint64_t ms = -1;
    isstream >> hours >> separator >> minutes >> separator >> seconds >> separator >> ms;
    while (ms == -1)
    {
        ms = seconds;
        seconds = minutes;
        minutes = hours;
        hours = 0;
    }
    return ((hours * 60 + minutes) * 60 + seconds) * 1000 + ms;
}
