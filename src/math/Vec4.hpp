#pragma once

struct Vec4
{
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        struct {
            float r;
            float g;
            float b;
            float a;
        };
        float array[4];
    };

    Vec4(float x, float y, float z, float w);
};
