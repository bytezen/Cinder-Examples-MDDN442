uniform vec3 lightDir;
varying float intensity;

void main() {
    intensity = dot(gl_Normal, lightDir);
    
    gl_Position = ftransform();    
}

