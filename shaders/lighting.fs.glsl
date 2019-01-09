//#version 330
//
//in vec3 vPosition;
//in vec3 vNormal;
//in vec2 vTexCoord;
//
//in float fog;
//
//uniform sampler2D uMainTextureSampler;
//
//out vec3 fFragColor;
//
//void main() {
//    vec3 texColor = texture(uMainTextureSampler, vTexCoord).xyz;
//    vec3 fogColor = vec3(1);
//
//    fFragColor = mix(texColor, fogColor, fog);
//}

#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D uMainTextureSampler;

out vec3 fFragColor;

float prodScal(vec3 vect1, vec3 vect2) {
    float prod = dot(normalize(vect1), normalize(vect2));
    if(prod <= 0) return 0;
    else return prod;
}

void main() {
    //// DIFFUSE IS BROKEN


    //tmp
    vec3 uLightPos = vec3(15);
    vec3 uKd = vec3(0,0,255);//texture(uMainTextureSampler, vTexCoord).rgb; //couleur de l'obj (diffus)
    vec3 uKs = vec3(255); //couleur du reflet(speculaire)
    vec3 uLightIntensity = vec3(8);
    float uShininess =64;

    float distanceLight = distance(vPosition, uLightPos);
    vec3 wi = normalize(uLightPos - vPosition);
    vec3 w0 = normalize(-vPosition);
    vec3 ahalf= normalize( (w0+wi)/2);

    vec3 KD = uKd * prodScal(wi, vNormal);
    vec3 KS = uKs * pow(prodScal(ahalf, vNormal), uShininess);

    vec3 objcolor= (uLightIntensity/(distanceLight*distanceLight))* mix(KD, KS, 0.9);
    //vec3 objcolor = ;
    fFragColor= objcolor;
}
