#pragma once

#include <vector>

#include <SDL.h>

#include "Renderer.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Karaoke.hpp"
#include "Audio.hpp"

#define APPLICATION_BASE_WIDTH 800
#define APPLICATION_BASE_HEIGHT 600

class Application
{
public:
    Application();
    Application(Application &&) = delete;
    Application(const Application &) = delete;
    Application &operator=(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    ~Application();

    bool is_initialized() const;
    void run();

private:
    bool m_is_initialized = false;
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    Renderer m_renderer;
    Font m_font;
    Mat4 m_font_scale = Mat4::identity();
    Mat4 m_projection = Mat4::identity();
    Karaoke m_karaoke = Karaoke();
    Audio m_audio;
    std::vector<Page>::const_iterator m_pages_iterator;
    bool m_running = false;
    float m_running_time = 0.0f;
    uint32_t m_audio_end_event = -1;

    bool initialize_SDL();
    bool initialize_OpenGL();

    void handle_events();
    void handle_events_window(SDL_Event event);
    void handle_events_keydown(SDL_Event event);
    void update();

    void set_projection_matrix();
    void set_projection_matrix(int window_width, int window_height);
};
