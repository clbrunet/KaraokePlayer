#include <iostream>

#include "Renderer.hpp"
#include "karaoke/Page.hpp"

Page::Page(const pugi::xml_node& page_node, const Font& font) :
    m_model(Mat4::identity())
{
    for (pugi::xml_node line_node : page_node)
    {
        m_lines.push_back(Line(line_node, font));
    }
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
    for (Line& line : m_lines)
    {
        line.set_timings();
    }
}

const std::vector<Line>& Page::lines() const
{
    return m_lines;
}

const Mat4& Page::model() const
{
    return m_model;
}

float Page::get_end_second() const
{
    if (m_lines.size() == 0)
    {
        return 0.0f;
    }
    return m_lines.back().get_end_second();
}
