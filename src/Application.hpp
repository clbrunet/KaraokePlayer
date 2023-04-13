#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>

#include <SDL.h>

#include "Renderer.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Song.hpp"

#define APPLICATION_WIDTH 800
#define APPLICATION_HEIGHT 600

class Application
{
public:
    Application();
    Application(Application &&) = default;
    Application(const Application &) = delete;
    Application &operator=(Application &&) = default;
    Application &operator=(const Application &) = delete;
    ~Application();

    bool is_initialized() const;
    void run();

private:
    bool m_is_initialized = false;
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    Renderer m_renderer = Renderer();
    Font m_font = Font();
    Mat4 m_font_scale = Mat4::identity();
    Mat4 m_projection = Mat4::identity();
    Song m_song = Song();
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

#endif
