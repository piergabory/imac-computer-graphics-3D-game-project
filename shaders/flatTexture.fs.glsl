#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in float fog;

const vec3 fogColor = vec3(0.8);

uniform sampler2D uMainTextureSampler;

out vec3 fFragColor;

void main() {
    vec3 texColor = texture(uMainTextureSampler, vTexCoord).xyz;
    fFragColor = mix(texColor, fogColor, fog);
}
