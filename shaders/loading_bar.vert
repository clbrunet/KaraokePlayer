#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;

uniform mat4 projection;
uniform mat4 scale;

out float v_u;

void main()
{
    gl_Position = projection * scale * position;

    v_u = texture_coordinates.x;
}
