#version 400 core

layout (location = 0) in vec4 position;

uniform float aspect_ratio;

uniform float first_syllabe_start_timing;
uniform float running_time;
uniform float noise_y_offset;

out vec2 v_noise_coordinates;

void main()
{
    gl_Position = position;

    float start_noise_scale = 3;
    float target_noise_scale = 1;
    float noise_scale_interpolation = smoothstep(0.0, first_syllabe_start_timing, running_time);
    float noise_scale = mix(start_noise_scale, target_noise_scale, noise_scale_interpolation);

    v_noise_coordinates = vec2(position.x * aspect_ratio, position.y)
        * noise_scale + vec2(0.0f, noise_y_offset);
}
