#pragma once

#include <vector>
#include <array>

#include <SDL.h>

#include "rendering/Renderer.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Karaoke.hpp"
#include "Audio.hpp"
#include "graphics/PlusMinusButton.hpp"

class Application
{
public:
    Application();
    Application(Application &&) = delete;
    Application(const Application &) = delete;
    Application &operator=(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    ~Application();

    bool is_initialized() const;
    void run();

    float aspect_ratio() const;
    const Mat4& projection() const;
    const Font& font() const;
    const Karaoke& karaoke() const;
    const Page* current_page() const;
    const std::array<PlusMinusButton, 2>& scale_plus_minus_buttons() const;
    float running_time() const;

private:
    static constexpr int WINDOW_BASE_WIDTH = 800;
    static constexpr int WINDOW_BASE_HEIGHT = 600;

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;

    float m_aspect_ratio = 0.0f;
    Mat4 m_projection = Mat4::identity();

    Font m_font;
    Karaoke m_karaoke;
    std::vector<Page>::const_iterator m_pages_iterator;

    uint32_t m_audio_end_event = -1;
    Audio m_audio;
    float m_audio_length = -1.0f;

    std::array<PlusMinusButton, 2> m_scale_plus_minus_buttons;

    Renderer m_renderer;

    bool m_is_initialized = false;
    bool m_is_running = false;
    float m_running_time = 0.0f;

    bool initialize_SDL();
    bool initialize_OpenGL();

    void handle_events();
    void handle_events_window(SDL_Event event);
    void handle_events_keydown(SDL_Event event);
    void update(float delta_time);

    void set_projection_matrix();
};
