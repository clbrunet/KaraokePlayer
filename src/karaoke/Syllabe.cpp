#include <iostream>

#include "Renderer.hpp"
#include "karaoke/Syllabe.hpp"

Syllabe::Syllabe(const pugi::xml_node& syllabe_node, const Font& font) :
    m_model(Mat4::identity())
{
    const unsigned char* chars = (const unsigned char*)syllabe_node.child("text").text().get();
    while (*chars != '\0')
    {
        m_letters.push_back(Letter(font, *chars));
        chars++;
    }
}

void Syllabe::set_models(float position)
{
    float letter_position = -((float)m_letters.size() / 2.0f) + 0.5f;
    for (Letter& letter : m_letters)
    {
        letter.set_model(letter_position);
        letter_position += 1.0f;
    }
    m_model.translate(Vec2(position * LETTER_BASE_WIDTH, 0.0f));
}

const std::vector<Letter>& Syllabe::letters() const
{
    return m_letters;
}

const Mat4& Syllabe::model() const
{
    return m_model;
}
