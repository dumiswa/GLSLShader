#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform int u_columns;
uniform int u_rows;

void main() {
    int x = int(floor(TexCoord.x * u_columns));
    int y = int(floor(TexCoord.y * u_rows));

    if ((x + y) % 2 == 0)
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White
    else
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black
}