#pragma once

#include "Program.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

class Application;
class Page;

class PlusMinusButtonsRenderer
{
public:
    PlusMinusButtonsRenderer() = default;
    PlusMinusButtonsRenderer(PlusMinusButtonsRenderer &&) = delete;
    PlusMinusButtonsRenderer(const PlusMinusButtonsRenderer &) = delete;
    PlusMinusButtonsRenderer &operator=(PlusMinusButtonsRenderer &&) = delete;
    PlusMinusButtonsRenderer &operator=(const PlusMinusButtonsRenderer &) = delete;
    ~PlusMinusButtonsRenderer();

    bool initialize();

    void render(const Application& application) const;

    static constexpr float PLUS_MINUS_BUTTON_WIDTH = 0.08f;
    static constexpr float PLUS_MINUS_BUTTON_HEIGHT = 0.10f;
    static constexpr float PLUS_MINUS_BUTTON_WIDTH_2 = PLUS_MINUS_BUTTON_WIDTH / 2.0f;
    static constexpr float PLUS_MINUS_BUTTON_HEIGHT_2 = PLUS_MINUS_BUTTON_HEIGHT / 2.0f;

private:
    static constexpr int INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_program;

    void initialize_OpenGL_objects();

    struct Vertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        Vertex(Vec3 position, Vec2 uvs);
    };
};
