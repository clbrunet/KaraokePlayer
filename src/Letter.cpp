#include "Letter.hpp"
#include "Renderer.hpp"

Letter::Letter(const Font& font, unsigned char c, Vec2 translation) :
    m_char_texture_coordinates(font.get_char_texture_coordinates(c)),
    m_model(Mat4::identity().scale(LETTERS_SCALE_FACTOR).translate(translation))
{
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
