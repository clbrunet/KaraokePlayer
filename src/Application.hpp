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

    bool is_initialized();
    void run();

private:
    bool m_is_initialized;
    SDL_Window* m_window;
};

#endif
