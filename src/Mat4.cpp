#include "Mat4.hpp"
#include "Vec2.hpp"
#include <cstring>

Mat4::Mat4()
{
    std::memset(array, 0, sizeof(float[4][4]));
}

Mat4::Mat4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    )
{
    array[0][0] = m00;
    array[0][1] = m01;
    array[0][2] = m02;
    array[0][3] = m03;

    array[1][0] = m10;
    array[1][1] = m11;
    array[1][2] = m12;
    array[1][3] = m13;

    array[2][0] = m20;
    array[2][1] = m21;
    array[2][2] = m22;
    array[2][3] = m23;

    array[3][0] = m30;
    array[3][1] = m31;
    array[3][2] = m32;
    array[3][3] = m33;
}

Mat4& Mat4::operator=(Mat4 const& rhs)
{
    std::memcpy(array, rhs.array, sizeof(float[4][4]));
    return *this;
}

 Mat4 Mat4::identity()
{
    return Mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
            );
}

Mat4& Mat4::scale(float factor)
{
    array[0][0] *= factor;
    array[1][1] *= factor;
    array[2][2] *= factor;
    return *this;
}

Mat4& Mat4::translate(Vec2 vec2)
{
    array[0][3] += vec2.x;
    array[1][3] += vec2.y;
    return *this;
}

Mat4 Mat4::operator*(Mat4 const& rhs) const
{
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.array[i][j] += array[i][k] * rhs.array[k][j];
            }
        }
    }
    return result;
}
