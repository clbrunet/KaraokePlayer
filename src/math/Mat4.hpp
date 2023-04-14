#ifndef MATH_MAT4_HPP
#define MATH_MAT4_HPP

struct Vec2;

struct Mat4
{
    float array[4][4];

    Mat4();
    Mat4(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33
        );
    Mat4& operator=(Mat4 const& rhs);

    static Mat4 identity();

    Mat4& scale(float factor);
    Mat4& scale(float x, float y, float z);
    Mat4& translate(Vec2 vec2);

    Mat4 operator*(Mat4 const& rhs) const;
};

#endif
