#include <algorithm>
#include <cstdint>
#include <iostream>

#include "karaoke/Karaoke.hpp"

Karaoke::Karaoke(const char* xml_path, const Font& font)
{
    load(xml_path, font);
}

bool Karaoke::load(const char* xml_path, const Font& font)
{
    pugi::xml_document doc;
    if (!doc.load_file(xml_path))
    {
        std::cerr << "Coundl't load the karaoke xml '" << xml_path << "'" << std::endl;
        return false;
    }
    for (pugi::xml_node page_node : doc.child("karaoke"))
    {
        m_pages.push_back(Page(page_node, font));
    }
    if (m_pages.size() == 0)
    {
        return true;
    }
    for (Page& page : m_pages)
    {
        page.set_models(Vec2::zero());
        page.set_timings();
    }
    m_first_syllabe_start_timing = m_pages.front().start_timing();
    m_last_syllabe_end_timing = m_pages.back().end_timing();
    add_empty_pages();
    return true;
}

const std::vector<Page>& Karaoke::pages() const
{
    return m_pages;
}

float Karaoke::first_syllabe_start_timing() const
{
    return m_first_syllabe_start_timing;
}

float Karaoke::last_syllabe_end_timing() const
{
    return m_last_syllabe_end_timing;
}

float Karaoke::get_speech_rate(float running_time) const
{
    for (const Page& page : m_pages)
    {
        if (page.start_timing() <= running_time && running_time <= page.end_timing())
        {
            return page.get_speech_rate(running_time);
        }
    }
    return -1.0f;
}

void Karaoke::add_empty_pages()
{
    constexpr float PAGES_TIMINGS_DIFF_MINIMUM = 5.0f;
    constexpr float EMPTY_PAGE_TO_NEXT_DIFF = 2.0f;
    static_assert(PAGES_TIMINGS_DIFF_MINIMUM > EMPTY_PAGE_TO_NEXT_DIFF,
            "A minimum page timings difference greater than"
            "the created differences will cause an infinite loop");
    float last_end_timing = 0.0f;
    for (size_t i = 0; i < m_pages.size(); i++) {
        float start_timing = m_pages[i].start_timing();
        float end_timing = m_pages[i].end_timing();
        if (start_timing - last_end_timing > PAGES_TIMINGS_DIFF_MINIMUM)
        {
            m_pages.insert(m_pages.begin() + i,
                    Page(last_end_timing, start_timing - EMPTY_PAGE_TO_NEXT_DIFF));
            i++;
        }
        last_end_timing = end_timing;
    }
}
