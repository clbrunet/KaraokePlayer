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
    m_renderer(),
    m_background_renderer(),
    m_font(),
    m_font_scale(Mat4::identity()),
    m_aspect_ratio(0.0f),
    m_projection(Mat4::identity()),
    m_karaoke(),
    m_audio(),
    m_pages_iterator(),
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
    if (!m_background_renderer.initialize())
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
    m_font_scale = Mat4::identity().scale(8.0f);
    m_aspect_ratio = (float)APPLICATION_BASE_WIDTH / (float)APPLICATION_BASE_HEIGHT;
    set_projection_matrix();
    if (!m_karaoke.load("assets/song.xml", m_font))
    {
        return;
    }
    if (!m_audio.load("assets/song.ogg", m_audio_end_event))
    {
        return;
    }
    m_pages_iterator = m_karaoke.pages().cbegin();

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
            APPLICATION_BASE_WIDTH, APPLICATION_BASE_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
    glViewport(0, 0, APPLICATION_BASE_WIDTH, APPLICATION_BASE_HEIGHT);
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
        float new_running_time = (float)SDL_GetTicks64() / 1000.0f - start_running_time;
        float delta_time = new_running_time - m_running_time;
        m_running_time = new_running_time;
        update(delta_time);
        m_background_renderer.render(m_aspect_ratio, m_karaoke.first_syllabe_start_timing(),
                m_running_time);
        const Page* page = (m_pages_iterator != m_karaoke.pages().cend())
            ? &*m_pages_iterator : nullptr;
        m_renderer.render(m_font, page, m_running_time, m_projection, m_font_scale);
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
            case SDL_WINDOWEVENT:
                handle_events_window(event);
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

void Application::handle_events_window(SDL_Event event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        int width = 0;
        int height = 0;
        SDL_GetWindowSize(m_window, &width, &height);
        glViewport(0, 0, width, height);
        m_aspect_ratio = (float)width / (float)height;
        set_projection_matrix();
    }
}

void Application::handle_events_keydown(SDL_Event event)
{
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        m_running = false;
    }
}

void Application::update(float delta_time)
{
    if (m_pages_iterator != m_karaoke.pages().cend()
        && m_pages_iterator->end_timing() < m_running_time)
    {
        m_pages_iterator++;
    }
    m_background_renderer.update(m_karaoke, m_running_time, delta_time);
}

void Application::set_projection_matrix()
{
    m_projection = Mat4::identity();
    m_projection.array[0][0] = 1.0f / m_aspect_ratio;
}
