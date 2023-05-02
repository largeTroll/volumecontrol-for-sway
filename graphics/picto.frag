#version 330 core

layout(location=0) out vec4 outColor;

uniform float u_brightness;

void main()
{
        vec3 color = vec3(1.0, 1.0, 1.0);
        outColor = vec4(color * u_brightness, 1.0);
        // outColor = vec4(1.0, 1.0, 1.0, 1.0);
}