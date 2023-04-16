#pragma once

#include "math/Vec2.hpp"
#include "math/Mat4.hpp"

class PlusMinusButton
{
public:
    PlusMinusButton() = default;
    PlusMinusButton(PlusMinusButton &&) = default;
    PlusMinusButton(const PlusMinusButton &) = default;
    PlusMinusButton &operator=(PlusMinusButton &&) = default;
    PlusMinusButton &operator=(const PlusMinusButton &) = default;
    ~PlusMinusButton() = default;

    PlusMinusButton(bool is_minus, Vec2 position);

    void update(float delta_time);

    bool is_clicked(Vec2 mouse_click_ratio);

    bool is_minus() const;
    const Mat4& model() const;
    float clicked_timer() const;

    static constexpr float CLICKED_TIMER_DURATION = 0.8f;

private:
    bool m_is_minus = false;
    Vec2 m_position = Vec2::zero();
    Mat4 m_model = Mat4::identity();
    float m_clicked_timer = 0.0f;
};
