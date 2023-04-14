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
    int letters_count = this->letters_count();
    float syllabe_start_local_position = -((float)letters_count / 2.0f) + 0.5f;
    for (Syllabe& syllabe : m_syllabes)
    {
        float syllabe_local_position = syllabe_start_local_position
            + ((float)syllabe.letters().size() / 2.0f) - 0.5f;
        syllabe.set_models(syllabe_local_position);
        syllabe_start_local_position += syllabe.letters().size();
    }
    m_model.translate(Vec2(local_position * LETTER_BASE_WIDTH, 0.0f));
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
        letters_count += syllabe.letters().size();
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
