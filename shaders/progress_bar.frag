#version 400 core

in float v_u;

uniform vec4 past_fragment_color;
uniform float audio_length;
uniform float running_time;

out vec4 out_color;

void main()
{
    float fragment_timing = mix(0.0f, audio_length, v_u);
    if (fragment_timing < running_time)
    {
        out_color = past_fragment_color;
    }
    else
    {
        out_color = vec4(0.5);
    }
}
