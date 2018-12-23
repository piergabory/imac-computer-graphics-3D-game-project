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
    //tmp
    vec3 uLightPos = vec3(15,15,15);
    vec3 uKd = vec3(100,100,255); //couleur de l'obj (diffus)
    vec3 uKs = vec3(255,255,255); //couleur du reflet(speculaire)
    vec3 uLightIntensity = vec3(8,8,8);
    float uShininess =32;

    float distanceLight = distance(vPosition, uLightPos);
    vec3 wi = normalize(uLightPos - vPosition);
    vec3 w0 = normalize(-vPosition);
    vec3 half= normalize( (w0+wi)/2);
    
    vec3 KD = ukd * prodScal(wi, vNormal);
    vec3 KS = uKs * pow(prodScal(half, vNormal), uShininess);

    vec3 objcolor= (uLightIntensity/(distanceLight*distanceLight))*(KD+KS);
    //vec3 objcolor = texture(uMainTextureSampler, vTexCoord).rgb;
    fFragColor= objcolor;
}