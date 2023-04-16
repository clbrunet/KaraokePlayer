#pragma once

#include "math/Mat4.hpp"

class Vec2;

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

    bool is_minus() const;
    const Mat4& model() const;

private:
    bool m_is_minus = false;
    Mat4 m_model = Mat4::identity();
};
