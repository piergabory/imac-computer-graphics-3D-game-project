
#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexUV;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 uSunPosition;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 sunPosition;

#define FOG_START 400.0
#define FOG_END 600.0
out float fog;

void main() {
    vec4 vertexPosition = (uMVMatrix * vec4(aVertexPosition, 1));
    // apply homogenous coord
    vPosition = vertexPosition.xyz / vertexPosition.w;


    vNormal = (uNormalMatrix * vec4(aVertexNormal, 0)).xyz;
    vTexCoord = aVertexTexUV;
    fog = 0; //1 - (FOG_END - length(vPosition)) / (FOG_END - FOG_START);
    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1);

    sunPosition = uSunPosition;
}
