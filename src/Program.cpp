#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/gl.h>

#include "Program.hpp"

Program::~Program()
{
    glDeleteProgram(m_program);
}

bool Program::initialize(const char* vertex_shader_path, const char* fragment_shader_path)
{
    unsigned int vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_path);
    if (vertex_shader == 0)
    {
        return false;
    }
    unsigned int fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_path);
    if (fragment_shader == 0)
    {
        glDeleteShader(vertex_shader);
        return false;
    }
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);
    bool isProgramLinked = link_program();
    glDetachShader(m_program, vertex_shader);
    glDetachShader(m_program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return isProgramLinked;
}

unsigned int Program::create_shader(GLenum shader_type, const char* shader_path) const
{
    unsigned int shader = glCreateShader(shader_type);

    std::ifstream ifstream(shader_path);
    std::stringstream buffer;
    buffer << ifstream.rdbuf();
    std::string string = buffer.str();
    const char* source = string.c_str();
    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE)
    {
        return shader;
    }
    char info_log[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, info_log);
    glDeleteShader(shader);
    std::cerr << "Shader '" << source << "' compilation error :\n" << info_log << std::flush;
    return 0;
}

bool Program::link_program()
{
    glLinkProgram(m_program);
    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (success == GL_TRUE)
    {
        return true;
    }
    char info_log[1024];
    glGetProgramInfoLog(m_program, 1024, nullptr, info_log);
    std::cerr << "Program link error :\n" << info_log << std::flush;
    return false;
}

void Program::use() const
{
    glUseProgram(m_program);
}

void Program::set_uniform_int(const char* location, int i)
{
    glUniform1i(glGetUniformLocation(m_program, location), i);
}
