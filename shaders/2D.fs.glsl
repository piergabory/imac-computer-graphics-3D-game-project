#version 330
in vec2 vTexCoord;
uniform sampler2D uMainTextureSampler;
out vec3 fFragColor;
void main() {
    fFragColor = texture(uMainTextureSampler, vTexCoord).xyz;
}
