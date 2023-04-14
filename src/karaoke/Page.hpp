#ifndef KARAOKE_PAGE_HPP
#define KARAOKE_PAGE_HPP

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

    void set_models(Vec2 page_translation);
    void set_timings();

    const std::vector<Line>& lines() const;
    const Mat4& model() const;
    float start_timing() const;
    float end_timing() const;

private:
    std::vector<Line> m_lines;
    Mat4 m_model;
    float m_start_timing;
    float m_end_timing;
};

#endif
