#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>

class Application
{
public:
    Application();
    Application(Application &&) = default;
    Application(const Application &) = default;
    Application &operator=(Application &&) = default;
    Application &operator=(const Application &) = default;
    ~Application();

    bool is_initialized() const;
    void run();

private:
    bool m_is_initialized;
    SDL_Window* m_window;
    SDL_GLContext m_context;
    bool m_running;

    bool initialize_SDL();
    bool initialize_OpenGL();

    void handle_events();
    void handle_events_keydown(SDL_Event event);
};

#endif
