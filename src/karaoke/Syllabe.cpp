#include <iostream>
#include <sstream>

#include "karaoke/Syllabe.hpp"
#include "rendering/PageRenderer.hpp"

Syllabe::Syllabe(const pugi::xml_node& syllabe_node, const Font& font)
{
    m_start_timing = (float)parse_ms_text(syllabe_node.child("start").text().get()) / 1000.0f;
    m_end_timing = (float)parse_ms_text(syllabe_node.child("end").text().get()) / 1000.0f;

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
    float letters_width = (float)letters_count() * PageRenderer::LETTER_BASE_WIDTH;
    float letter_local_position = (letters_width - PageRenderer::LETTER_BASE_WIDTH) * -0.5f;
    for (Letter& letter : m_letters)
    {
        letter.set_model(letter_local_position);
        letter_local_position += PageRenderer::LETTER_BASE_WIDTH;
    }
}

void Syllabe::set_timings()
{
    if (m_letters.size() == 0)
    {
        return;
    }
    float timing = m_start_timing;
    float letter_duration = (m_end_timing - m_start_timing) / letters_count();
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

float Syllabe::start_timing() const
{
    return m_start_timing;
}

float Syllabe::end_timing() const
{
    return m_end_timing;
}

float Syllabe::get_speech_rate() const
{
    return letters_count() / (m_end_timing - m_start_timing);
}

uint64_t Syllabe::parse_ms_text(const std::string& text)
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
