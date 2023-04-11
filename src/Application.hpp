#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>

#include "Renderer.hpp"

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
    bool m_running = false;

    bool initialize_SDL();
    bool initialize_OpenGL();

    void handle_events();
    void handle_events_keydown(SDL_Event event);
};

#endif
