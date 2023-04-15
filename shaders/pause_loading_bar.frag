#version 400 core

in float v_u;

uniform float start_timing;
uniform float end_timing;
uniform float running_time;
uniform vec4 past_fragment_color;
uniform vec4 old_past_fragment_color;

out vec4 out_color;

void main()
{
    float fragment_timing = mix(start_timing, end_timing, v_u);
    if (fragment_timing < running_time)
    {
        float interpolation = (running_time - fragment_timing) / 5.0;
        out_color = mix(past_fragment_color, old_past_fragment_color, interpolation);
    }
    else
    {
        out_color = vec4(1.0);
    }
}
