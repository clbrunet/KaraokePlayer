#include <iostream>

#include "graphics/PlusMinusButton.hpp"
#include "math/Vec2.hpp"
#include "rendering/PlusMinusButtonsRenderer.hpp"

PlusMinusButton::PlusMinusButton(bool is_minus, Vec2 position) :
    m_is_minus(is_minus),
    m_position(position),
    m_model(Mat4::identity().translate(position))
{
}

bool PlusMinusButton::is_clicked(Vec2 mouse_click_ratio) const
{
    Vec2 bottom_left(
            (m_position.x - PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_WIDTH_2) * 0.5f + 0.5f,
            (m_position.y - PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_HEIGHT_2) * 0.5f + 0.5f);
    Vec2 top_right(
            (m_position.x + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_WIDTH_2) * 0.5f + 0.5f,
            (m_position.y + PlusMinusButtonsRenderer::PLUS_MINUS_BUTTON_HEIGHT_2) * 0.5f + 0.5f);
    if (bottom_left.x <= mouse_click_ratio.x && mouse_click_ratio.x <= top_right.x
        && bottom_left.y <= mouse_click_ratio.y && mouse_click_ratio.y <= top_right.y)
    {
        return true;
    }
    return false;
}

bool PlusMinusButton::is_minus() const
{
    return m_is_minus;
}

const Mat4& PlusMinusButton::model() const
{
    return m_model;
}
