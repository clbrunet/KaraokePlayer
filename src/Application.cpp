#include <cassert>
#include <cstdio>
#include <iostream>

#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Application.hpp"

Application::Application() :
    m_is_initialized(false),
    m_window(nullptr),
    m_context(nullptr),
    m_renderer(Renderer()),
    m_font(Font()),
    m_font_scale(Mat4()),
    m_song(Song()),
    m_pages_iterator(std::vector<Page>::const_iterator()),
    m_running(false),
    m_running_time(0.0f)
{
    if (!initialize_SDL())
    {
        return;
    }
    if (!initialize_OpenGL())
    {
        return;
    }
    if (!m_renderer.initialize())
    {
        return;
    }
    if (!m_font.load("assets/font.xml", "assets/font.bmp"))
    {
        return;
    }
    m_font_scale = Mat4::identity().scale(1.5f);
    if (!m_song.load("assets/song.xml", m_font, "assets/song.ogg", m_audio_end_event))
    {
        return;
    }
    m_pages_iterator = m_song.pages().cbegin();

    m_is_initialized = true;
}

bool Application::initialize_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Coundl't initialize video subsystem." << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_window = SDL_CreateWindow("Karaoke Player",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            APPLICATION_WIDTH, APPLICATION_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!m_window)
    {
        std::cerr << "Coundl't create SDL window." << std::endl;
        return false;
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context)
    {
        std::cerr << "Coundl't create OpenGL context." << std::endl;
        return false;
    }

    SDL_GL_SetSwapInterval(1);

    m_audio_end_event = SDL_RegisterEvents(1);
    if (m_audio_end_event == -1)
    {
        std::cerr << "Coundl't register events." << std::endl;
        return false;
    }
    return true;
}

bool Application::initialize_OpenGL()
{
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    if (version == 0)
    {
        std::cerr << "Coundl't initialize glad." << std::endl;
        return false;
    }
    glViewport(0, 0, APPLICATION_WIDTH, APPLICATION_HEIGHT);
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
    SDL_PauseAudio(0);
    float start_running_time = (float)SDL_GetTicks64() / 1000.0f;
    m_running_time = 0.0f;
    while (m_running)
    {
        handle_events();
        if (!m_running)
        {
            break;
        }
        m_running_time = (float)SDL_GetTicks64() / 1000.0f - start_running_time;
        update();
        const Page* page = (m_pages_iterator != m_song.pages().cend())
            ? &*m_pages_iterator : nullptr;
        m_renderer.render(m_font, page, m_running_time, m_font_scale);
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
        if (event.type == m_audio_end_event)
        {
            m_running = false;
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

void Application::update()
{
    if (m_pages_iterator != m_song.pages().cend()
        && m_pages_iterator->get_end_second() < m_running_time)
    {
        m_pages_iterator++;
    }
}
