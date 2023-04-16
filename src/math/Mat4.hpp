#pragma once

struct Vec2;
struct Vec3;

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
    Mat4(const Mat4& src);
    Mat4& operator=(Mat4 const& rhs);

    static Mat4 identity();

    Vec3 get_scale();
    void set_scale(Vec3 scale);

    Mat4& scale(float factor);
    Mat4& scale(Vec3 scale);
    Mat4& translate(Vec2 vec2);

    Mat4 operator*(Mat4 const& rhs) const;
};
