#version 330

in vec3 vPosition;

out vec3 fFragColor;

void main() {
    fFragColor = abs(vec3(0.5) + vPosition);
}
