#version 330 core

uniform float LINE_WIDTH;
uniform vec4 COLOR;
uniform float BLEND_FACTOR; // 1.5..2.5

in vec4 position;
in vec2 lineCenter;

void main() {
    vec4 color = COLOR;
    float d = length(lineCenter - position.xy);
    float w = LINE_WIDTH;

    if (d > w) {
        color.w = 0;
    } else {
        color.w *= pow(float((w-d)/w), BLEND_FACTOR);
    }

    gl_FragColor = color;
}
