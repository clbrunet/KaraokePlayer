#version 400 core

in float v_u;

uniform float running_time;
uniform float start_timing;
uniform float end_timing;
uniform vec4 already_sung_text_color;

out vec4 out_color;

void main()
{
    float timing = mix(start_timing, end_timing, v_u);
    if (running_time > timing)
    {
        out_color = already_sung_text_color;
    }
    else
    {
        out_color = vec4(1.0);
    }
}
