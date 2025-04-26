#version 330

layout(location = 0) in vec3 vertex;
out vec2 TexCoord;

uniform vec2 offset;

void main() {
    //applies movement to the quad using the offset
    gl_Position = vec4(vertex + vec3(offset, 0.0), 1.0);

    //passes texture coordinates unchanged
    TexCoord = vertex.xy * 0.5 + 0.5;
}
