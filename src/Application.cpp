#include <cassert>
#include <cstdio>
#include <iostream>

#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Application.hpp"

Application::Application()
{
    if (!initialize_SDL())
    {
        return;
    }
    if (!initialize_OpenGL())
    {
        return;
    }
    m_aspect_ratio = (float)WINDOW_BASE_WIDTH / (float)WINDOW_BASE_HEIGHT;
    set_projection_matrix();
    if (!m_font.load("assets/font.xml", "assets/font.bmp"))
    {
        return;
    }
    if (!m_karaoke.load("assets/song.xml", m_font))
    {
        return;
    }
    m_pages_iterator = m_karaoke.pages().cbegin();
    m_audio_length = m_audio.load("assets/song.ogg", m_audio_end_event);
    if (m_audio_length < 0.0f)
    {
        return;
    }
    m_scale_plus_minus_buttons[0] = PlusMinusButton(true,
            Vec2(-1.0f + ProgressBarRenderer::PROGRESS_BAR_HEIGHT_2
                + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_WIDTH_2,
                -1.0f + ProgressBarRenderer::PROGRESS_BAR_HEIGHT
                + ProgressBarRenderer::PROGRESS_BAR_HEIGHT_2
                + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_HEIGHT_2));
    m_scale_plus_minus_buttons[1] = PlusMinusButton(false,
            Vec2(-1.0f + ProgressBarRenderer::PROGRESS_BAR_HEIGHT
                + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_WIDTH
                + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_WIDTH_2,
                -1.0f + ProgressBarRenderer::PROGRESS_BAR_HEIGHT
                + ProgressBarRenderer::PROGRESS_BAR_HEIGHT_2
                + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_HEIGHT_2));
    if (!m_renderer.initialize(m_karaoke, m_audio_length))
    {
        return;
    }

    m_is_initialized = true;
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

    m_is_running = true;
    SDL_PauseAudio(0);
    float start_running_time = (float)SDL_GetTicks64() / 1000.0f;
    m_running_time = 0.0f;
    while (m_is_running)
    {
        handle_events();
        if (!m_is_running)
        {
            break;
        }
        float new_running_time = (float)SDL_GetTicks64() / 1000.0f - start_running_time;
        float delta_time = new_running_time - m_running_time;
        m_running_time = new_running_time;
        update(delta_time);
        m_renderer.render(*this);
        SDL_GL_SwapWindow(m_window);
    }
}

float Application::aspect_ratio() const
{
    return m_aspect_ratio;
}

const Mat4& Application::projection() const
{
    return m_projection;
}

const Font& Application::font() const
{
    return m_font;
}

const Karaoke& Application::karaoke() const
{
    return m_karaoke;
}

const Page* Application::current_page() const
{
    if (m_pages_iterator == m_karaoke.pages().cend())
    {
        return nullptr;
    }
    return &*m_pages_iterator;
}

const Mat4& Application::scale() const
{
    return m_scale;
}

const std::array<PlusMinusButton, 2>& Application::scale_plus_minus_buttons() const
{
    return m_scale_plus_minus_buttons;
}

float Application::running_time() const
{
    return m_running_time;
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
            WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT,
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
    if (m_audio_end_event == (uint32_t)-1)
    {
        std::cerr << "Coundl't register events." << std::endl;
        return false;
    }
    return true;
}

bool Application::initialize_OpenGL()
{
    if (gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0)
    {
        std::cerr << "Coundl't initialize glad." << std::endl;
        return false;
    }
    glViewport(0, 0, WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT);
    return true;
}

void Application::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
                handle_events_window(event);
                break;
            case SDL_KEYDOWN:
                handle_events_keydown(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handle_events_mousebuttondown(event);
                break;
            case SDL_QUIT:
                m_is_running = false;
                break;
        }
        if (event.type == m_audio_end_event)
        {
            m_is_running = false;
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
        m_is_running = false;
    }
}

void Application::handle_events_mousebuttondown(SDL_Event event)
{
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(m_window, &width, &height);
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    Vec2 mouse_click_ratio((float)x / (float)width, (float)(height - y) / (float)height);
    if (m_scale_plus_minus_buttons[0].is_clicked(mouse_click_ratio))
    {
        m_scale.set_scale((m_scale.get_scale() - 0.2f).clamp(0.2f, 2.0f));
    }
    else if (m_scale_plus_minus_buttons[1].is_clicked(mouse_click_ratio))
    {
        m_scale.set_scale((m_scale.get_scale() + 0.2f).clamp(0.2f, 2.0f));
    }
}

void Application::update(float delta_time)
{
    if (m_pages_iterator != m_karaoke.pages().cend()
        && m_pages_iterator->end_timing() < m_running_time)
    {
        m_pages_iterator++;
    }
    m_renderer.update(*this, delta_time);
}

void Application::set_projection_matrix()
{
    m_projection = Mat4::identity();
    m_projection.array[0][0] = 1.0f / m_aspect_ratio;
}
