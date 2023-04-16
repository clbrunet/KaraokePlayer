#include <iostream>

#include <glad/gl.h>

#include "rendering/TextsRenderer.hpp"
#include "Application.hpp"
#include "graphics/Text.hpp"
#include "graphics/Character.hpp"

TextsRenderer::~TextsRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool TextsRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_character_program.initialize("shaders/character.vert", "shaders/character.frag"))
    {
        return false;
    }
    m_character_program.use();
    m_character_program.set_uniform_int("sampler", 0);
    return true;
}

void TextsRenderer::render(const Application& application) const
{
    glBindVertexArray(m_vertex_array);
    m_character_program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, application.font().image().texture());
    for (const Text& text : application.texts())
    {
        for (const Character& character : text.characters())
        {
            m_character_program.set_uniform_vec2("char_texture_bottom_left",
                    character.texture_coordinates_bottom_left());
            m_character_program.set_uniform_vec2("char_texture_top_right",
                    character.texture_coordinates_top_right());
            m_character_program.set_uniform_mat4("projection_model",
                    text.model() * application.projection() * character.model());
            glDrawElements(GL_TRIANGLES, CHARACTER_INDICES_COUNT, GL_UNSIGNED_INT, 0);
        }
    }
}

void TextsRenderer::initialize_OpenGL_objects()
{
    CharacterVertex m_character_vertices[] =
    {
        CharacterVertex(Vec3(-CHARACTER_BASE_WIDTH_2, -CHARACTER_BASE_HEIGHT_2, 0.0f), Vec2(0.0f, 0.0f)),
        CharacterVertex(Vec3(-CHARACTER_BASE_WIDTH_2, CHARACTER_BASE_HEIGHT_2, 0.0f), Vec2(0.0f, 1.0f)),
        CharacterVertex(Vec3(CHARACTER_BASE_WIDTH_2, CHARACTER_BASE_HEIGHT_2, 0.0f), Vec2(1.0f, 1.0f)),
        CharacterVertex(Vec3(CHARACTER_BASE_WIDTH_2, -CHARACTER_BASE_HEIGHT_2, 0.0f), Vec2(1.0f, 0.0f)),
    };
    unsigned int m_character_indices[CHARACTER_INDICES_COUNT] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_character_vertices),
            m_character_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_character_indices),
            m_character_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(CharacterVertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(CharacterVertex), (void*)offsetof(CharacterVertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(CharacterVertex::uvs) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(CharacterVertex), (void*)offsetof(CharacterVertex, uvs));
    glEnableVertexAttribArray(1);
}

TextsRenderer::CharacterVertex::CharacterVertex(Vec3 position, Vec2 uvs) :
    position(position),
    uvs(uvs)
{
}
