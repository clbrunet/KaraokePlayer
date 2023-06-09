#pragma once

#include "graphics/Font.hpp"
#include "math/Mat4.hpp"

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

    void set_model(float local_position);
    void set_timings(float start_timing, float end_timing);

    Vec2 texture_coordinates_bottom_left() const;
    Vec2 texture_coordinates_top_right() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;

private:
    Font::CharTextureCoordinates m_char_texture_coordinates;
    Mat4 m_model = Mat4::identity();
    float m_start_timing = 0.0f;
    float m_end_timing = 0.0f;
};
