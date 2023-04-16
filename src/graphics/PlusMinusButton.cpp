#include "graphics/PlusMinusButton.hpp"
#include "math/Vec2.hpp"

PlusMinusButton::PlusMinusButton(bool is_minus, Vec2 position) :
    m_is_minus(is_minus),
    m_model(Mat4::identity().translate(position))
{
}

bool PlusMinusButton::is_minus() const
{
    return m_is_minus;
}

const Mat4& PlusMinusButton::model() const
{
    return m_model;
}
