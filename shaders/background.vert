#version 400 core

layout (location = 0) in vec4 position;

out vec2 v_position;

void main()
{
    gl_Position = position;

    v_position = position.xy;
}
