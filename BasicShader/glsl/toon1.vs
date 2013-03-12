uniform vec3 lightDir;
varying float intensity;

void main() {
    vec3 l = lightDir;
    
    intensity = dot(gl_Normal, l);
    
    gl_Position = ftransform();    
}

