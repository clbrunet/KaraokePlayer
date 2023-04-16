#pragma once

struct Vec3
{
    union {
        struct {
            float x;
            float y;
            float z;
        };
        struct {
            float r;
            float g;
            float b;
        };
        float array[3];
    };

    Vec3(float x, float y, float z);

    const Vec3& clamp(float min, float max);

    static Vec3 zero();

    Vec3 operator+(float rhs) const;
    Vec3 operator-(float rhs) const;
};
