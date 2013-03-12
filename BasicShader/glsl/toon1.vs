uniform vec3 lightDir;
varying float intensity;

void main() {
    vec3 n = normalize(gl_Normal);
    vec3 l = lightDir;
    l *= -1.0;    
    
    intensity = dot(n, l);
    
    gl_Position = ftransform();    
}

