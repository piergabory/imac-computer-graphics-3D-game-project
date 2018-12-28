#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D uMainTextureSampler;

out vec3 fFragColor;

void main() {
    //tmp
    vec3 uLightPos = vec3(15,15,15);
    vec3 uLightIntensity = vec3(8,8,8);
    vec3 uLightColor = vec3(255,255,255);
    float ambiantStrength = 0.1;

    vec3 ambiant= ambiantStrength * uLightColor;
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPos-vPosition);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * uLightColor;
    vec3 objcolor = texture(uMainTextureSampler, vTexCoord).rgb;
    fFragColor = (ambiant + diffuse) * objcolor;
}