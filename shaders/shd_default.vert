#version 330 core

layout(location = 0)in vec2 in_pos;
layout(location = 1)in vec2 in_tex;

uniform mat4 projection_view;
uniform mat4 model;

out vec2 texCoord;

void main()
{
    gl_Position = projection_view * model * vec4(in_pos, 0.0f, 1.0f);
    texCoord = in_tex;
}