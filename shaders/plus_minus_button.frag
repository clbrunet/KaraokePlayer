#version 400 core

in vec2 v_uvs;

uniform bool is_minus;
uniform float clicked_timer;
uniform float clicked_timer_duration;

out vec4 out_color;

void main()
{
    const float WIDTH_2 = 0.07;
    const float LENGTH_2 = 0.35;
    if (!is_minus
            && 0.5 - LENGTH_2 < v_uvs.y && v_uvs.y < 0.5 + LENGTH_2
            && 0.5 - WIDTH_2 < v_uvs.x && v_uvs.x < 0.5 + WIDTH_2)
    {
        out_color = vec4(vec3(0.0), 1.0);
        return;
    }
    if (0.5 - LENGTH_2 < v_uvs.x && v_uvs.x < 0.5 + LENGTH_2
            && 0.5 - WIDTH_2 < v_uvs.y && v_uvs.y < 0.5 + WIDTH_2)
    {
        out_color = vec4(vec3(0.0), 1.0);
        return;
    }
    vec4 clicked_color = vec4(vec3(0.4), 1.0);
    vec4 base_color = vec4(vec3(1.0), 1.0);
    float interpolation = clicked_timer / clicked_timer_duration;
    out_color = mix(base_color, clicked_color, interpolation);
}
