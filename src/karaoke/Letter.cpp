#include <iostream>

#include "karaoke/Letter.hpp"
#include "Renderer.hpp"

Letter::Letter(const Font& font, unsigned char c) :
    m_char_texture_coordinates(font.get_char_texture_coordinates(c)),
    m_model(Mat4::identity())
{
}

void Letter::set_model(float position)
{
    m_model.translate(Vec2(position * LETTER_BASE_WIDTH, 0.0f));
}

Vec2 Letter::bottom_left() const
{
    return m_char_texture_coordinates.bottom_left;
}

Vec2 Letter::top_right() const
{
    return m_char_texture_coordinates.top_right;
}

const Mat4& Letter::model() const
{
    return m_model;
}
