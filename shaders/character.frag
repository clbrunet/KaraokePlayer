#version 400 core

in vec2 v_texture_coordinates;

uniform sampler2D sampler;

out vec4 out_color;

void main()
{
    vec4 color = texture(sampler, v_texture_coordinates);
    if (color.rgb == vec3(0.0, 1.0, 0.0) || color.a == 0.0)
    {
        discard;
    }
    out_color = color;
}
