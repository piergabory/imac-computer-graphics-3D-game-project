#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D uMainTextureSampler;

out vec3 fFragColor;

void main() {
    fFragColor = texture(uMainTextureSampler, vTexCoord).xyz;
}
