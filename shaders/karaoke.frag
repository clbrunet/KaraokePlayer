#version 400 core

in vec2 v_texture_coordinates;

uniform sampler2D sampler;

out vec4 out_color;

void main()
{
  out_color = texture(sampler, v_texture_coordinates);
}
