#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Font.hpp"

class Renderer
{
public:
    Renderer() = default;
    Renderer(Renderer &&) = default;
    Renderer(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = default;
    Renderer &operator=(const Renderer &) = delete;
    ~Renderer() = default;

    bool initialize();
    void render() const;

private:
    Font m_font = Font();
};

#endif
