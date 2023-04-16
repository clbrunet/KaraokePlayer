#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uvs;

uniform mat4 model;
uniform float aspect_ratio;

out vec2 v_uvs;

void main()
{
    gl_Position = model * position;

    v_uvs = vec2((uvs.x - 0.5) * aspect_ratio + 0.5, uvs.y);
}
