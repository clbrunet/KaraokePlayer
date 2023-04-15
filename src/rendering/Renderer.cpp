#include <iostream>

#include <glad/gl.h>

#include "rendering/Renderer.hpp"
#include "Application.hpp"

bool Renderer::initialize(const Karaoke& karaoke, float audio_length)
{
    if (!m_background_renderer.initialize(karaoke, audio_length))
    {
        return false;
    }
    if (!m_pause_loading_bar_renderer.initialize())
    {
        return false;
    }
    if (!m_page_renderer.initialize())
    {
        return false;
    }
    return true;
}

void Renderer::update(const Application& application, float delta_time)
{
    m_background_renderer.update(application, delta_time);
}

void Renderer::render(const Application& application) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_background_renderer.render(application);
    m_pause_loading_bar_renderer.render(application);
    m_page_renderer.render(application);
}
