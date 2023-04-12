#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;

uniform vec2 bottom_left;
uniform vec2 top_right;

out vec2 v_texture_coordinates;

void main()
{
  gl_Position = position;

  v_texture_coordinates = mix(bottom_left, top_right, texture_coordinates);
}
