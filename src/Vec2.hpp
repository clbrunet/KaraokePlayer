#ifndef VEC2_HPP
#define VEC2_HPP

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
};

#endif
