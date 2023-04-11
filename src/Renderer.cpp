#include <glad/gl.h>

#include "Renderer.hpp"

bool Renderer::initialize()
{
    glClearColor(0.3f, 0.1f, 0.7f, 1.0f);

    if (!m_font.load("assets/font.xml", "assets/font.bmp"))
    {
        return false;
    }
    return true;
}

void Renderer::render() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
