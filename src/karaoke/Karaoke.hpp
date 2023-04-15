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
    float first_syllabe_start_timing() const;
    float last_syllabe_end_timing() const;
    float get_speech_rate(float running_time) const;

private:
    std::vector<Page> m_pages;
    float m_first_syllabe_start_timing = 0.0f;
    float m_last_syllabe_end_timing = 0.0f;

    void add_empty_pages();
};
