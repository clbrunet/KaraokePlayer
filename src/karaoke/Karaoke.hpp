#pragma once

#include <vector>

#include <pugixml.hpp>

#include "karaoke/Page.hpp"

class Karaoke
{
public:
    Karaoke() = default;
    Karaoke(Karaoke &&) = default;
    Karaoke(const Karaoke &) = default;
    Karaoke &operator=(Karaoke &&) = default;
    Karaoke &operator=(const Karaoke &) = default;
    ~Karaoke() = default;

    Karaoke(const char* xml_path, const Font& font);

    bool load(const char* xml_path, const Font& font);

    const std::vector<Page>& pages() const;

private:
    std::vector<Page> m_pages;

    void add_empty_pages();
};
