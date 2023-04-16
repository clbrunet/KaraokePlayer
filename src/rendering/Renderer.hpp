#pragma once

#include "rendering/BackgroundRenderer.hpp"
#include "rendering/ProgressBarRenderer.hpp"
#include "rendering/PageRenderer.hpp"
#include "rendering/PauseLoadingBarRenderer.hpp"

class Karaoke;
class Application;

class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer &&) = delete;
    Renderer(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = delete;
    Renderer &operator=(const Renderer &) = delete;
    ~Renderer() = default;

    bool initialize(const Karaoke& karaoke, float audio_length);

    void update(const Application& application, float delta_time);
    void render(const Application& application) const;

private:
    BackgroundRenderer m_background_renderer;
    ProgressBarRenderer m_progress_bar_renderer;
    PauseLoadingBarRenderer m_pause_loading_bar_renderer;
    PageRenderer m_page_renderer;
};
