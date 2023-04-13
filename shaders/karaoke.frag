#version 400 core

in vec2 v_texture_coordinates;
in float v_u;

uniform sampler2D sampler;
uniform float running_time;
uniform float letter_start_timing;
uniform float letter_end_timing;
uniform vec4 already_sung_text_color;

out vec4 out_color;

void main()
{
    vec4 color = texture(sampler, v_texture_coordinates);
    if (color.rgb == vec3(0.0, 1.0, 0.0) || color.a == 0.0)
    {
        discard;
    }
    float letter_timing = mix(letter_start_timing, letter_end_timing, v_u);
    if (color == vec4(1.0) && running_time > letter_timing)
    {
        out_color = already_sung_text_color;
    }
    else
    {
        out_color = color;
    }
}
