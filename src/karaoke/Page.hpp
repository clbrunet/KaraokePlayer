#ifndef KARAOKE_PAGE_HPP
#define KARAOKE_PAGE_HPP

#include <vector>

#include "Line.hpp"

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

    void set_models();

    const std::vector<Line>& lines() const;
    float get_end_ms() const;

private:
    std::vector<Line> m_lines;
};

#endif
