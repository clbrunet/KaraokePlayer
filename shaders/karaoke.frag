#version 400 core

in vec2 v_texture_coordinates;

uniform sampler2D sampler;
uniform float running_time;
uniform float letter_start_timing;
uniform float letter_end_timing;

out vec4 out_color;

void main()
{
    if (texture(sampler, v_texture_coordinates).rgb != vec3(0.0, 0.0, 0.0))
    {
        discard;
    }
    float letter_timing = mix(letter_start_timing, letter_end_timing, v_texture_coordinates.x);
    if (running_time > letter_timing)
    {
        out_color = vec4(1.0, 0.5, 0.0, 1.0);
    }
    else
    {
        out_color = vec4(1.0);
    }
}
