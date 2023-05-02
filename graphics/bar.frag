#version 330 core

in vec2 v_Color;
out vec4 outColor;

uniform float u_brightness;
uniform float u_volume;

void main()
{
        if (v_Color.x < u_volume){
                outColor = vec4(vec3(v_Color.y), 1.0);
        } else {
                // outColor = vec4(1.0) - vec4(vec3(u_brightness).xyz, 1.0);
                outColor = vec4(1.0) - vec4(vec3(v_Color.y), 0.0);
        }
}