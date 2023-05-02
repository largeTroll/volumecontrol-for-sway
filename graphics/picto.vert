#version 330 core

layout(location = 0) in vec2 v_pos;

uniform float u_scale;
uniform vec2 u_offset;

void main()
{
        vec2 scaled = v_pos * u_scale;
        vec2 translated = scaled + u_offset;
        gl_Position = vec4(translated.xy, 0.0, 1.0);
}