#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

out vec2 v_TextureCoordinate;

void main() {
    v_TextureCoordinate = a_TextureCoordinate;
    gl_Position = vec4(a_Position, 1.0);
}


#type pixel
#version 460 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TextureCoordinate;
uniform sampler2D u_Texture;

void main() {
    o_Color = texture(u_Texture, v_TextureCoordinate);
}
