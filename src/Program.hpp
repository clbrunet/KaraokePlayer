#pragma once

#include <glad/gl.h>

struct Vec2;
struct Vec4;
struct Mat4;

class Program
{
public:
    Program() = default;
    Program(Program &&) = default;
    Program(const Program &) = default;
    Program &operator=(Program &&) = default;
    Program &operator=(const Program &) = default;
    ~Program();

    bool initialize(const char* vertex_shader_path, const char* fragment_shader_path);
    void use() const;

    void set_uniform_int(const char* location, int i) const;
    void set_uniform_float(const char* location, float f) const;
    void set_uniform_vec2(const char* location, Vec2 vec2) const;
    void set_uniform_vec4(const char* location, Vec4 vec4) const;
    void set_uniform_mat4(const char* location, const Mat4& mat4) const;

private:
    unsigned int m_program = 0;

    unsigned int create_shader(GLenum shader_type, const char* content) const;
    bool link_program();
};
