#pragma once

#include <vector>

#include "karaoke/Line.hpp"

class Page
{
public:
    Page() = delete;
    Page(Page &&) = default;
    Page(const Page &) = default;
    Page &operator=(Page &&) = default;
    Page &operator=(const Page &) = default;
    ~Page() = default;

    Page(const pugi::xml_node& page_node, const Font& font);
    Page(float start_timing, float end_timing);

    void set_models(Vec2 page_translation);
    void set_timings();

    const std::vector<Line>& lines() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;
    float get_speech_rate(float running_time) const;

private:
    std::vector<Line> m_lines;
    Mat4 m_model;
    float m_start_timing;
    float m_end_timing;
};
