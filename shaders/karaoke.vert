#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_coordinates;

out vec2 v_texture_coordinates;

void main()
{
  gl_Position = position;

  v_texture_coordinates = texture_coordinates;
}
