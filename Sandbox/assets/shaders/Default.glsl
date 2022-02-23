#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

void main() {
    v_Color = a_Color;
    gl_Position = vec4(a_Position, 1.0);
}


#type pixel
#version 460 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;

void main() {
    o_Color = v_Color;
}
