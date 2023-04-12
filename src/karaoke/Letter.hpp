#ifndef LETTER_HPP
#define LETTER_HPP

#include "Font.hpp"
#include "Mat4.hpp"

class Letter
{
public:
    Letter() = delete;
    Letter(Letter &&) = default;
    Letter(const Letter &) = default;
    Letter &operator=(Letter &&) = default;
    Letter &operator=(const Letter &) = default;
    ~Letter() = default;

    Letter(const Font& font, unsigned char c);

    void set_model(float position);

    Vec2 bottom_left() const;
    Vec2 top_right() const;
    const Mat4& model() const;

private:
    Font::CharTextureCoordinates m_char_texture_coordinates;
    Mat4 m_model;
};

#endif
