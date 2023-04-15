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

    static Vec3 zero();
};
