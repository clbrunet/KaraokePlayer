#pragma once

#include "Program.hpp"
#include "math/Mat4.hpp"
#include "math/Vec2.hpp"
#include "math/Vec3.hpp"

class Application;

class TextsRenderer
{
public:
    TextsRenderer() = default;
    TextsRenderer(TextsRenderer &&) = delete;
    TextsRenderer(const TextsRenderer &) = delete;
    TextsRenderer &operator=(TextsRenderer &&) = delete;
    TextsRenderer &operator=(const TextsRenderer &) = delete;
    ~TextsRenderer();

    bool initialize();

    void render(const Application& application) const;

    static constexpr float CHARACTER_BASE_WIDTH = 0.05f;
    static constexpr float CHARACTER_BASE_HEIGHT = 0.175f;
    static constexpr float CHARACTER_BASE_WIDTH_2 = CHARACTER_BASE_WIDTH / 2.0f;
    static constexpr float CHARACTER_BASE_HEIGHT_2 = CHARACTER_BASE_HEIGHT / 2.0f;

private:
    static constexpr int CHARACTER_INDICES_COUNT = 6;
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_element_buffer = 0;
    Program m_character_program;

    void initialize_OpenGL_objects();

    struct CharacterVertex
    {
        Vec3 position = Vec3::zero();
        Vec2 uvs = Vec2::zero();

        CharacterVertex(Vec3 position, Vec2 uvs);
    };
};
