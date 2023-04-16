#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;

out float v_u;

void main()
{
    gl_Position = position;

    v_u = texture_coordinates.x;
}
