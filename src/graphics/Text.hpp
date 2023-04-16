#pragma once

#include <vector>

#include "graphics/Character.hpp"
#include "math/Mat4.hpp"

class Font;
class Vec2;

class Text
{
public:
    Text() = delete;
    Text(Text &&) = default;
    Text(const Text &) = default;
    Text &operator=(Text &&) = default;
    Text &operator=(const Text &) = default;
    ~Text() = default;

    enum class Alignment
    {
        Left,
        Center,
        Right,
    };

    Text(const Font& font, const char* str, Vec2 position, Alignment alignment);

    const std::vector<Character>& characters() const;
    const Mat4& model() const;

private:
    std::vector<Character> m_characters;
    Mat4 m_model = Mat4::identity();
};
