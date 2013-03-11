#version 110

varying vec3 normal;
varying vec4 worldPosition;
varying vec4 worldN;
varying vec3 viewDir;

uniform vec4 camLoc;

void main()
{
	normal = gl_NormalMatrix * gl_Normal;
	
	gl_Position = ftransform();
    
    //this is a hack because the obj file was drawing upside down
    //gl_Position is read only...so pass to a temp variable and then change
    vec4 p = gl_Position;
    p.y *= -1.0; 
    gl_Position = p;
    
	worldPosition = gl_ModelViewMatrix * gl_Vertex;
	worldN = normalize( vec4( gl_NormalMatrix * gl_Normal, 0 ) );
	vec4 viewDir4 = normalize( camLoc - worldPosition );
	viewDir = vec3( viewDir4.xyz );
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
