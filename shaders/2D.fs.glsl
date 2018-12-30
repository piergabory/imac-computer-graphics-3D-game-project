#version 330
in vec2 vTexCoord;
uniform sampler2D uMainTextureSampler;
out vec4 fFragColor;
void main() {
    vec4 texColor = texture(uMainTextureSampler, vTexCoord);
    if(texColor.a < 0.1) //discard if alpha is next to zero
        discard;
    fFragColor = texColor;
    //fFragColor = vec4(255,0,0,1.0); test shader
}
