#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;

uniform mat4 projection_model;

uniform vec2 char_texture_bottom_left;
uniform vec2 char_texture_top_right;

out vec2 v_texture_coordinates;

void main()
{
    gl_Position = projection_model * position;

    v_texture_coordinates = mix(char_texture_bottom_left, char_texture_top_right,
            texture_coordinates);
}
