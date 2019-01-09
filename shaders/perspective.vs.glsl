
#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexUV;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

#define FOG_START 400.0
#define FOG_END 600.0
out float fog;

void main() {
    vPosition = (uMVMatrix * vec4(aVertexPosition, 1)).xyz;
    vNormal = (uNormalMatrix * vec4(aVertexNormal, 0)).xyz;
    vTexCoord = aVertexTexUV;
    fog = 0; //1 - (FOG_END - length(vPosition)) / (FOG_END - FOG_START);
    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1);
}
