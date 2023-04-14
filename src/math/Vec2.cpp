#include "math/Vec2.hpp"

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::zero()
{
    return Vec2(0.0f, 0.0f);
}
