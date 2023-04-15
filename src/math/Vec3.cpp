#include "math/Vec3.hpp"

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::zero()
{
    return Vec3(0.0f, 0.0f, 0.0f);
}
