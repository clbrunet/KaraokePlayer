#pragma once

#include "graphics/Font.hpp"
#include "math/Mat4.hpp"

class Vec2;

class Character
{
public:
    Character() = delete;
    Character(Character &&) = default;
    Character(const Character &) = default;
    Character &operator=(Character &&) = default;
    Character &operator=(const Character &) = default;
    ~Character() = default;

    Character(const Font& font, unsigned char c, float x_position);

    Vec2 texture_coordinates_bottom_left() const;
    Vec2 texture_coordinates_top_right() const;
    const Mat4& model() const;

private:
    Font::CharTextureCoordinates m_char_texture_coordinates;
    Mat4 m_model = Mat4::identity();
};
