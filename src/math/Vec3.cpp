#include "math/Vec3.hpp"
#include <cassert>

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

const Vec3& Vec3::clamp(float min, float max)
{
    assert(min < max);

    if (x < min)
    {
        x = min;
    }
    else if (max < x)
    {
        x = max;
    }
    if (y < min)
    {
        y = min;
    }
    else if (max < y)
    {
        y = max;
    }
    if (z < min)
    {
        z = min;
    }
    else if (max < z)
    {
        z = max;
    }
    return *this;
}

Vec3 Vec3::zero()
{
    return Vec3(0.0f, 0.0f, 0.0f);
}

Vec3 Vec3::operator+(float rhs) const
{
    return Vec3(x + rhs, y + rhs, z + rhs);
}

Vec3 Vec3::operator-(float rhs) const
{
    return Vec3(x - rhs, y - rhs, z - rhs);
}
