#include <cassert>

#include <SDL.h>

#include "Program.hpp"

Program::Program() : m_is_initialized(false), m_window(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fputs("Coundl't initialize video subsystem.\n", stderr);
        return;
    }

    m_window = SDL_CreateWindow("Karaoke Player"
        , SDL_WINDOWPOS_CENTERED
        , SDL_WINDOWPOS_CENTERED
        , 800, 600
        , SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!m_window)
    {
        fputs("Couldn't create SDL window.\n", stderr);
        return;
    }

    m_is_initialized = true;
}

Program::~Program()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Program::is_initialized()
{
    return m_is_initialized;
}

void Program::run()
{
    assert(is_initialized() && "Check Program::is_initialized before calling Program::run");

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
            }
        }

        if (!running)
            break;

        // Rendering karaoke here
    }
}
