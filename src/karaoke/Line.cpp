#include <iostream>

#include "karaoke/Line.hpp"
#include "Renderer.hpp"

Line::Line(const pugi::xml_node& line_node, const Font& font) :
    m_model(Mat4::identity()),
    m_start_timing(0.0f),
    m_end_timing(0.0f)
{
    for (pugi::xml_node word_node : line_node)
    {
        m_words.push_back(Word(word_node, font));
    }
}

void Line::set_models(float local_position)
{
    m_model = Mat4::identity().translate(Vec2(0.0f, local_position));

    // spread word positions around 0
    float letters_width = (float)letters_count() * LETTER_BASE_WIDTH;
    float spaces_width = (float)spaces_count() * WORDS_SPACING_BASE_WIDTH;
    float word_start_local_position = (letters_width - LETTER_BASE_WIDTH + spaces_width) * -0.5f;
    for (Word& word : m_words)
    {
        float word_letters_width = (float)word.letters_count() * LETTER_BASE_WIDTH;
        float word_local_position = word_start_local_position
            + 0.5f * (word_letters_width - LETTER_BASE_WIDTH);
        word.set_models(word_local_position);
        word_start_local_position += WORDS_SPACING_BASE_WIDTH + word_letters_width;
    }
}

void Line::set_timings()
{
    if (m_words.size() == 0)
    {
        return;
    }
    for (Word& word : m_words)
    {
        word.set_timings();
    }
    m_start_timing = m_words.front().start_timing();
    m_end_timing = m_words.back().end_timing();
}

const std::vector<Word>& Line::words() const
{
    return m_words;
}

int Line::letters_count() const
{
    int letters_count = 0;
    for (const Word& word : m_words)
    {
        letters_count += word.letters_count();
    }
    return letters_count;
}

int Line::spaces_count() const
{
    if (m_words.size() == 0)
    {
        return 0;
    }
    return m_words.size() - 1;
}

const Mat4& Line::model() const
{
    return m_model;
}

float Line::start_timing() const
{
    return m_start_timing;
}

float Line::end_timing() const
{
    return m_end_timing;
}

float Line::get_speech_rate(float running_time) const
{
    for (const Word& word : m_words)
    {
        if (word.start_timing() <= running_time && running_time <= word.end_timing())
        {
            return word.get_speech_rate(running_time);
        }
    }
    return -1.0f;
}
