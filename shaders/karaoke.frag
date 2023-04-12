#version 400 core

in vec2 v_texture_coordinates;

uniform sampler2D sampler;

out vec4 out_color;

void main()
{
  if (texture(sampler, v_texture_coordinates).rgb != vec3(0, 0, 0))
  {
    discard;
  }
  out_color = vec4(1);
}
