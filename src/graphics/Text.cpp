#include <cstring>

#include "graphics/Text.hpp"
#include "math/Vec2.hpp"
#include "rendering/TextsRenderer.hpp"

Text::Text(const Font& font, const char* str, Vec2 position, Alignment alignment) :
    m_model(Mat4::identity().translate(position))
{
    size_t length = std::strlen(str);
    if (length == 0)
    {
        return;
    }
    float characters_width = (float)length * TextsRenderer::CHARACTER_BASE_WIDTH;
    int str_shift = 0;
    float character_x_position = 0.0f;
    float character_x_position_shift = 0.0f;
    switch (alignment) {
        case Alignment::Left:
            str_shift = 1;
            character_x_position = TextsRenderer::CHARACTER_BASE_WIDTH_2;
            character_x_position_shift = TextsRenderer::CHARACTER_BASE_WIDTH;
            break;
        case Alignment::Center:
            str_shift = 1;
            character_x_position = (characters_width - TextsRenderer::CHARACTER_BASE_WIDTH) * -0.5f;
            character_x_position_shift = TextsRenderer::CHARACTER_BASE_WIDTH;
            break;
        case Alignment::Right:
            str_shift = -1;
            str += length - 1;
            character_x_position = -TextsRenderer::CHARACTER_BASE_WIDTH_2;
            character_x_position_shift = -TextsRenderer::CHARACTER_BASE_WIDTH;
            break;
    }
    while (length > 0)
    {
        m_characters.push_back(Character(font, *str, character_x_position));
        str += str_shift;
        character_x_position += character_x_position_shift;
        length--;
    }
}

const std::vector<Character>& Text::characters() const
{
    return m_characters;
}

const Mat4& Text::model() const
{
    return m_model;
}
