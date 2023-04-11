#include <cassert>
#include <cstdio>

#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Application.hpp"

Application::Application() :
    m_is_initialized(false),
    m_window(nullptr),
    m_context(nullptr)
{
    if (!initialize_SDL())
    {
        return;
    }
    if (!initialize_OpenGL())
    {
        return;
    }

    m_is_initialized = true;
}

bool Application::initialize_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fputs("Coundl't initialize video subsystem.\n", stderr);
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_window = SDL_CreateWindow("Karaoke Player",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!m_window)
    {
        fputs("Couldn't create SDL window.\n", stderr);
        return false;
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context)
    {
        fputs("Couldn't create OpenGL context.\n", stderr);
        return false;
    }

    SDL_GL_SetSwapInterval(1);

    return true;
}

bool Application::initialize_OpenGL()
{
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    if (version == 0)
    {
        fputs("Couldn't initialize glad.\n", stderr);
        return false;
    }
    printf("OpenGL version : %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    return true;
}

Application::~Application()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Application::is_initialized() const
{
    return m_is_initialized;
}

void Application::run()
{
    assert(is_initialized() && "Check Application::is_initialized before calling Application::run");

    m_running = true;
    while (m_running)
    {
        handle_events();
        if (!m_running)
        {
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // Rendering karaoke here

        SDL_GL_SwapWindow(m_window);
    }
}

void Application::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                handle_events_keydown(event);
                break;
            case SDL_QUIT:
                m_running = false;
                break;
        }
    }
}

void Application::handle_events_keydown(SDL_Event event)
{
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        m_running = false;
    }
}
