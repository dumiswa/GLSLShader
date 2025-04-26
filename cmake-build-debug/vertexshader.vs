#version 330 core

layout(location = 0) in vec2 aPos;
out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = (aPos + vec2(1.0)) / 2.0;  // Transforming to range [0,1]
}