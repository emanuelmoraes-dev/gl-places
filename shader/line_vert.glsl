#version 330 core

uniform mat4 MVP;
uniform vec2 VIEW_PORT;

layout (location = 0) in vec3 inPosition;

out vec4 position;
out vec2 lineCenter;

void main() {
    position = MVP * vec4(inPosition, 1.0);
    gl_Position = position;
    lineCenter = 0.5 * (position.xy + vec2(1, 1)) * VIEW_PORT;
}
