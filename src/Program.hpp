#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <glad/gl.h>

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
    unsigned int get() const;

private:
    unsigned int m_program = 0;

    unsigned int create_shader(GLenum shader_type, const char* content) const;
    bool link_program();
};

#endif
