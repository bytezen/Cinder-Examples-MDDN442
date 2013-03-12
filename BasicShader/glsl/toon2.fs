
uniform vec3 lightDir;    
varying vec3 normal;

void main() {     
    vec3 l = lightDir * -1.0;
    float intensity = dot(normalize(normal), l);
    
    vec4 c;
    
    if( intensity > 0.95 ) {
        c = vec4(1.0,0.5,0.5,1.0);
    }
    else if ( intensity > 0.5 ) {
        c =  vec4(.6,0.3,0.3,1.0);        
    }
    else if ( intensity > 0.25 ) {
        c =  vec4(.4,0.2,0.2,1.0);    
    }
    else 
    {
        c =  vec4(0.2,0.1,0.1,1.0);        
    }
    
    gl_FragColor = c;
}

