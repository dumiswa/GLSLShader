#version 330

in vec2 TexCoord;
out vec4 sColor;

uniform int u_columns;
uniform int u_rows;
uniform float u_time;
uniform float u_speed;
uniform vec2 u_mouse;
uniform vec2 u_quadCenter;  //the screen-space position of the quad
uniform int u_patternType;

void main() {
    //apply scaling to the pattern
    float scale = 1.0 + 0.3 * sin(u_time * u_speed);
    vec2 centeredTex = (TexCoord - 0.5) * scale;

    //apply rotation matrix
    float angle = u_time * u_speed;
    mat2 rotationMatrix = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
    vec2 transformedTex = rotationMatrix * centeredTex + 0.5;
    vec3 baseColor;

    if (u_patternType == 0) {
        //regular Checkerboard Pattern
        int x = int(floor(transformedTex.x * u_columns));
        int y = int(floor(transformedTex.y * u_rows));
        baseColor = ((x + y) % 2 == 0) ? vec3(1.0) : vec3(0.0);
    } else {
        //radial Checkerboard Pattern
        float rings = length(transformedTex) * u_columns * 2.0;
        baseColor = (mod(floor(rings), 2.0) == 0.0) ? vec3(1.0) : vec3(0.0);
    }

    //fixes the lighting to follow the mouse
    vec2 localMousePos = (u_mouse - u_quadCenter) * 2.0; //convert screen space to local quad space
    float distance = length(TexCoord - (localMousePos * 0.5 + 0.5)); //adjusted to match TexCoord range
    float brightness = 1.2 - distance * 8.0;
    brightness = clamp(brightness, 0.3, 1.0);


    vec3 finalColor = mix(vec3(0.1), vec3(1.0), baseColor) * brightness;
    sColor = vec4(finalColor, 1.0);
}
