#include <iostream>

#include "Renderer.hpp"
#include "karaoke/Page.hpp"

Page::Page(const pugi::xml_node& page_node, const Font& font) :
    m_model(Mat4::identity()),
    m_start_timing(0.0f),
    m_end_timing(0.0f)
{
    for (pugi::xml_node line_node : page_node)
    {
        m_lines.push_back(Line(line_node, font));
    }
}

Page::Page(float start_timing, float end_timing) :
    m_lines(),
    m_model(Mat4::identity()),
    m_start_timing(start_timing),
    m_end_timing(end_timing)
{
}

void Page::set_models(Vec2 page_translation)
{
    m_model = Mat4::identity().translate(page_translation);

    // spread line positions around 0
    int lines_count = m_lines.size();
    float lines_height = (float)lines_count * LETTER_BASE_HEIGHT;
    float spacings_height = (float)(lines_count - 1) * LINES_SPACING_BASE_HEIGHT;
    float line_local_position = (lines_height - LETTER_BASE_HEIGHT + spacings_height) * 0.5f;
    for (Line& line : m_lines)
    {
        line.set_models(line_local_position);
        line_local_position -= LINES_SPACING_BASE_HEIGHT + LETTER_BASE_HEIGHT;
    }
}

void Page::set_timings()
{
    if (m_lines.size() == 0)
    {
        return;
    }
    for (Line& line : m_lines)
    {
        line.set_timings();
    }
    m_start_timing = m_lines.front().start_timing();
    m_end_timing = m_lines.back().end_timing();
}

const std::vector<Line>& Page::lines() const
{
    return m_lines;
}

const Mat4& Page::model() const
{
    return m_model;
}

float Page::start_timing() const
{
    return m_start_timing;
}

float Page::end_timing() const
{
    return m_end_timing;
}

float Page::get_speech_rate(float running_time) const
{
    for (const Line& line : m_lines)
    {
        if (line.start_timing() <= running_time && running_time <= line.end_timing())
        {
            return line.get_speech_rate(running_time);
        }
    }
    return -1.0f;
}
