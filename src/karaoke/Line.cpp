#include <iostream>

#include "Line.hpp"
#include "Renderer.hpp"

Line::Line(const pugi::xml_node& line_node, const Font& font) :
    m_model(Mat4::identity())
{
    for (pugi::xml_node word_node : line_node)
    {
        m_words.push_back(Word(word_node, font));
    }
}

void Line::set_models(float position)
{
    int letters_count = this->letters_count();
    float word_start_position = -((float)letters_count / 2.0f) + 0.5f;
    for (Word& word : m_words)
    {
        float word_position = word_start_position
            + ((float)word.letters_count() / 2.0f) - 0.5f;
        word.set_models(word_position);
        word_start_position += 1 + word.letters_count();
    }
    m_model.translate(Vec2(0.0f, -position * LETTER_BASE_HEIGHT));
}

const std::vector<Word>& Line::words() const
{
    return m_words;
}

int Line::letters_count() const
{
    if (m_words.size() == 0)
    {
        return 0;
    }
    int letters_count = -1;
    for (const Word& word : m_words)
    {
        letters_count += 1 + word.letters_count();
    }
    return letters_count;
}

const Mat4& Line::model() const
{
    return m_model;
}
