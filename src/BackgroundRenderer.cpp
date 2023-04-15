#include <iostream>

#include <glad/gl.h>

#include "BackgroundRenderer.hpp"
#include "karaoke/Karaoke.hpp"
#include "math/Vec2.hpp"
#include "math/Vec4.hpp"
#include "math/Mat4.hpp"
#include "math/utils.hpp"
#include "karaoke/Letter.hpp"
#include "karaoke/Page.hpp"
#include "karaoke/Syllabe.hpp"
#include "karaoke/Word.hpp"

BackgroundRenderer::~BackgroundRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool BackgroundRenderer::initialize()
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/background.vert", "shaders/background.frag"))
    {
        return false;
    }
    m_program.use();
    return true;
}

void BackgroundRenderer::initialize_OpenGL_objects()
{
    BackgroundVertex m_background_vertices[] =
    {
        BackgroundVertex(Vec3(-1.0f, -1.0f, 0.0f)),
        BackgroundVertex(Vec3(-1.0f, 1.0f, 0.0f)),
        BackgroundVertex(Vec3(1.0f, 1.0f, 0.0f)),
        BackgroundVertex(Vec3(1.0f, -1.0f, 0.0f)),
    };
    unsigned int m_background_indices[BACKGROUND_INDICES_COUNT] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_background_vertices),
            m_background_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_background_indices),
            m_background_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(BackgroundVertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(BackgroundVertex), (void*)offsetof(BackgroundVertex, position));
    glEnableVertexAttribArray(0);
}

void BackgroundRenderer::update(const Karaoke& karaoke, float running_time, float delta_time)
{
    float desired_speed = NOISE_Y_OFFSET_NORMAL_SPEED;
    if (running_time < karaoke.first_syllabe_start_timing()
        || karaoke.last_syllabe_end_timing() < running_time)
    {
        desired_speed = 0.0f;
    }
    float speech_rate = karaoke.get_speech_rate(running_time);
    if (speech_rate > 0.0f)
    {
        desired_speed *= speech_rate / 5.0f;
    }
    m_noise_y_offset_speed = advance_towards(m_noise_y_offset_speed, desired_speed,
            NOISE_Y_OFFSET_ACCELERATION * delta_time);
    m_noise_y_offset += m_noise_y_offset_speed * delta_time;
}

void BackgroundRenderer::render(float aspect_ratio, const Karaoke& karaoke,
        float audio_length, float running_time) const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_float("aspect_ratio", aspect_ratio);
    m_program.set_uniform_float("first_syllabe_start_timing", karaoke.first_syllabe_start_timing());
    m_program.set_uniform_float("last_syllabe_end_timing", karaoke.last_syllabe_end_timing());
    m_program.set_uniform_float("audio_length", audio_length);
    m_program.set_uniform_float("running_time", running_time);
    m_program.set_uniform_float("noise_y_offset", m_noise_y_offset);
    glDrawElements(GL_TRIANGLES, BACKGROUND_INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

BackgroundRenderer::BackgroundVertex::BackgroundVertex(Vec3 position) :
    position(position)
{
}
