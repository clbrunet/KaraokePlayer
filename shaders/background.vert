#version 400 core

layout (location = 0) in vec4 position;

uniform float aspect_ratio;

out vec2 v_noise_coordinates;

void main()
{
    gl_Position = position;

    v_noise_coordinates = vec2(position.x * aspect_ratio, position.y);
}
