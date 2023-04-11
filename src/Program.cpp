#include <cassert>
#include <cstdio>

#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Program.hpp"

Program::Program() : m_is_initialized(false), m_window(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fputs("Coundl't initialize video subsystem.\n", stderr);
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

    SDL_GLContext context = SDL_GL_CreateContext(m_window);
    if (!context)
    {
        fputs("Couldn't create OpenGL context.\n", stderr);
        return;
    }

    SDL_GL_SetSwapInterval(1);

    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    if (version == 0)
    {
        fputs("Couldn't initialize glad.\n", stderr);
        return;
    }
    printf("OpenGL version : %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

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
