#include <iostream>

#include "karaoke/Letter.hpp"
#include "Renderer.hpp"

Letter::Letter(const Font& font, unsigned char c) :
    m_char_texture_coordinates(font.get_char_texture_coordinates(c)),
    m_model(Mat4::identity())
{
}

void Letter::set_model(float local_position)
{
    m_model = Mat4::identity().translate(Vec2(local_position, 0.0f));
}

void Letter::set_timings(float start_timing, float end_timing)
{
    m_start_timing = start_timing;
    m_end_timing = end_timing;
}

Vec2 Letter::texture_coordinates_bottom_left() const
{
    return m_char_texture_coordinates.bottom_left;
}

Vec2 Letter::texture_coordinates_top_right() const
{
    return m_char_texture_coordinates.top_right;
}

const Mat4& Letter::model() const
{
    return m_model;
}

float Letter::start_timing() const
{
    return m_start_timing;
}

float Letter::end_timing() const
{
    return m_end_timing;
}
