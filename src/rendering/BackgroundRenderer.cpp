#include <iostream>

#include <glad/gl.h>

#include "rendering/BackgroundRenderer.hpp"
#include "Application.hpp"
#include "math/utils.hpp"

BackgroundRenderer::~BackgroundRenderer()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_element_buffer);
}

bool BackgroundRenderer::initialize(const Karaoke& karaoke, float audio_length)
{
    initialize_OpenGL_objects();
    if (!m_program.initialize("shaders/background.vert", "shaders/background.frag"))
    {
        return false;
    }
    m_program.use();
    m_program.set_uniform_float("first_syllabe_start_timing", karaoke.first_syllabe_start_timing());
    m_program.set_uniform_float("last_syllabe_end_timing", karaoke.last_syllabe_end_timing());
    m_program.set_uniform_float("audio_length", audio_length);
    return true;
}

void BackgroundRenderer::initialize_OpenGL_objects()
{
    Vertex m_vertices[] =
    {
        Vertex(Vec3(-1.0f, -1.0f, 0.0f)),
        Vertex(Vec3(-1.0f, 1.0f, 0.0f)),
        Vertex(Vec3(1.0f, 1.0f, 0.0f)),
        Vertex(Vec3(1.0f, -1.0f, 0.0f)),
    };
    unsigned int m_indices[INDICES_COUNT] =
    {
        0, 1, 2,
        0, 2, 3,
    };

    glGenVertexArrays(1, &m_vertex_array);
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_element_buffer);

    glBindVertexArray(m_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
}

void BackgroundRenderer::update(const Application& application, float delta_time)
{
    float desired_speed = NOISE_Y_OFFSET_NORMAL_SPEED;
    if (application.running_time() < application.karaoke().first_syllabe_start_timing()
        || application.karaoke().last_syllabe_end_timing() < application.running_time())
    {
        desired_speed = 0.0f;
    }
    float speech_rate = application.karaoke().get_speech_rate(application.running_time());
    if (speech_rate > 0.0f)
    {
        desired_speed *= speech_rate / 5.0f;
    }
    m_noise_y_offset_speed = advance_towards(m_noise_y_offset_speed, desired_speed,
            NOISE_Y_OFFSET_MAX_ACCELERATION * delta_time);
    m_noise_y_offset += m_noise_y_offset_speed * delta_time;
}

void BackgroundRenderer::render(const Application& application) const
{
    glBindVertexArray(m_vertex_array);
    m_program.use();
    m_program.set_uniform_float("aspect_ratio", application.aspect_ratio());
    m_program.set_uniform_float("running_time", application.running_time());
    m_program.set_uniform_float("noise_y_offset", m_noise_y_offset);
    glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, 0);
}

BackgroundRenderer::Vertex::Vertex(Vec3 position) :
    position(position)
{
}
