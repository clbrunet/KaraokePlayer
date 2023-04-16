#include "graphics/Character.hpp"

Character::Character(const Font& font, unsigned char c, float x_position) :
    m_char_texture_coordinates(font.get_char_texture_coordinates(c)),
    m_model(Mat4::identity().translate(Vec2(x_position, 0.0f)))
{
}

Vec2 Character::texture_coordinates_bottom_left() const
{
    return m_char_texture_coordinates.bottom_left;
}

Vec2 Character::texture_coordinates_top_right() const
{
    return m_char_texture_coordinates.top_right;
}

const Mat4& Character::model() const
{
    return m_model;
}
