#pragma once

#include "Program.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

class Application;
class Page;

class PauseLoadingBarRenderer
{
public:
    PauseLoadingBarRenderer() = default;
    PauseLoadingBarRenderer(PauseLoadingBarRenderer &&) = delete;
    PauseLoadingBarRenderer(const PauseLoadingBarRenderer &) = delete;
    PauseLoadingBarRenderer &operator=(PauseLoadingBarRenderer &&) = delete;
    PauseLoadingBarRenderer &operator=(const PauseLoadingBarRenderer &) = delete;
    ~PauseLoadingBarRenderer();

    bool initialize();

    void render(const Application& application) const;

private:
    static constexpr float LOADING_BAR_WIDTH_2 = 0.8f;
    static constexpr float LOADING_BAR_HEIGHT_2 = 0.06f;
    static constexpr int INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;

    void initialize_OpenGL_objects();

    void render_pause_loading_bar(const Page& page) const;

    struct Vertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        Vertex(Vec3 position, Vec2 uvs);
    };
};
