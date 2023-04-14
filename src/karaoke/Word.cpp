#include <iostream>

#include "Renderer.hpp"
#include "karaoke/Word.hpp"

Word::Word(const pugi::xml_node& word_node, const Font& font) :
    m_model(Mat4::identity())
{
    for (pugi::xml_node syllabe_node : word_node)
    {
        m_syllabes.push_back(Syllabe(syllabe_node, font));
    }
}

void Word::set_models(float local_position)
{
    m_model.translate(Vec2(local_position, 0.0f));

    // spread syllabe positions around 0
    float letters_width = (float)letters_count() * LETTER_BASE_WIDTH;
    float syllabe_start_local_position = (letters_width - LETTER_BASE_WIDTH) * -0.5f;
    for (Syllabe& syllabe : m_syllabes)
    {
        float syllabe_letters_width = (float)syllabe.letters_count() * LETTER_BASE_WIDTH;
        float syllabe_local_position = syllabe_start_local_position
            + 0.5f * (syllabe_letters_width - LETTER_BASE_WIDTH);
        syllabe.set_models(syllabe_local_position);
        syllabe_start_local_position += syllabe_letters_width;
    }
}

void Word::set_timings()
{
    for (Syllabe& syllabe : m_syllabes)
    {
        syllabe.set_timings();
    }
}

const std::vector<Syllabe>& Word::syllabes() const
{
    return m_syllabes;
}

int Word::letters_count() const
{
    int letters_count = 0;
    for (const Syllabe& syllabe : m_syllabes)
    {
        letters_count += syllabe.letters_count();
    }
    return letters_count;
}

const Mat4& Word::model() const
{
    return m_model;
}

float Word::get_end_second() const
{
    if (m_syllabes.size() == 0)
    {
        return 0.0f;
    }
    return m_syllabes.back().get_end_second();
}
