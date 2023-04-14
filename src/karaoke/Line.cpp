#include <iostream>

#include "karaoke/Line.hpp"
#include "Renderer.hpp"

Line::Line(const pugi::xml_node& line_node, const Font& font) :
    m_model(Mat4::identity())
{
    for (pugi::xml_node word_node : line_node)
    {
        m_words.push_back(Word(word_node, font));
    }
}

void Line::set_models(float local_position)
{
    m_model.translate(Vec2(0.0f, local_position));

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
    for (Word& word : m_words)
    {
        word.set_timings();
    }
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

float Line::get_end_second() const
{
    if (m_words.size() == 0)
    {
        return 0.0f;
    }
    return m_words.back().get_end_second();
}
