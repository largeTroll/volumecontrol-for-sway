#version 330 core

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_tex;

out vec2 v_Color;

void main()
{
        v_Color = v_tex;
        gl_Position = vec4(v_pos.xy, 0.0, 1.0);
}