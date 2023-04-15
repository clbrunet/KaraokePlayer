#version 400 core

layout (location = 0) in vec4 position;

uniform float aspect_ratio;

uniform float first_syllabe_start_timing;
uniform float last_syllabe_end_timing;
uniform float audio_length;
uniform float running_time;
uniform float noise_y_offset;

out vec2 v_noise_coordinates;

void main()
{
    gl_Position = position;

    float zoomed_out_noise_scale = 3;
    float zoomed_in_noise_scale = 1;
    float noise_scale_interpolation = 1.0;
    if (running_time < first_syllabe_start_timing)
    {
        noise_scale_interpolation = smoothstep(0.0, first_syllabe_start_timing, running_time);
    }
    else if (last_syllabe_end_timing < running_time)
    {
        noise_scale_interpolation
            = -smoothstep(last_syllabe_end_timing, audio_length, running_time) + 1.0;
    }
    float noise_scale = mix(zoomed_out_noise_scale, zoomed_in_noise_scale, noise_scale_interpolation);

    v_noise_coordinates = vec2(position.x * aspect_ratio, position.y)
        * noise_scale + vec2(0.0f, noise_y_offset);
}
