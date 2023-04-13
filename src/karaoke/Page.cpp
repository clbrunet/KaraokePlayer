#include <iostream>

#include "Renderer.hpp"
#include "karaoke/Page.hpp"

Page::Page(const pugi::xml_node& page_node, const Font& font)
{
    for (pugi::xml_node line_node : page_node)
    {
        m_lines.push_back(Line(line_node, font));
    }
}

void Page::set_models()
{
    int lines_count = m_lines.size();
    float line_position = -((float)lines_count / 2.0f) + 0.5f;
    const float spacing = 0.7f * LETTER_BASE_HEIGHT;
    for (Line& line : m_lines)
    {
        line.set_models(line_position + line_position * spacing);
        line_position += 1.0f;
    }
}

const std::vector<Line>& Page::lines() const
{
    return m_lines;
}

float Page::get_end_ms() const
{
    if (m_lines.size() == 0)
    {
        return 0.0f;
    }
    return m_lines.back().get_end_ms();
}
