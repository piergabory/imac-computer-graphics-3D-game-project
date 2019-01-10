#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 sunPosition;
in float fog;

uniform sampler2D uMainTextureSampler;

out vec3 fFragColor;

// color constants
const vec3 fogColor = vec3(0.4,0.4,0.5);
const vec3 sunColor = vec3(1);
const vec3 sunSpecular = vec3(1);
const vec3 ambient = vec3(0,0,0.1);

// light parameters constants
const float shine = 40.0;


void main() {
    vec3 specular = vec3(0);
    vec3 normal = normalize(vNormal);
    vec3 view = normalize(-vPosition);
    vec3 light = normalize(sunPosition);


    // diffuse
    float intensity = max(dot(normal, light), 0.0);
    intensity = intensity * 0.9 + 0.1;
    vec3 diffuse = texture(uMainTextureSampler, vTexCoord).rgb;

    // specular
    if (intensity > 0.0) {
        vec3 halfVector = normalize(light + view);
        float specularAngle = max(dot(halfVector, normal), 0.0);
        specular = specular * pow(specularAngle, shine);
    }

    vec3 lighting = max(intensity * diffuse + specular, ambient);

    // final color
    fFragColor = mix(lighting, fogColor, fog);
}
