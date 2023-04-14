#ifndef MATH_VEC2_HPP
#define MATH_VEC2_HPP

struct Vec2
{
    union {
        struct {
            float x;
            float y;
        };
        struct {
            float u;
            float v;
        };
        float array[2];
    };

    Vec2(float x, float y);

    static Vec2 zero();
};

#endif
