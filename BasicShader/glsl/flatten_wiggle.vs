#version 110

uniform bool wiggle;
uniform float time;

void main()
{
	vec4 v = vec4(gl_Vertex);
//    v.z = 2.0;
    v.z = wiggle == true ? sin(5.0*v.x + time*.9)*1.5 : sin(5.0*v.x) * 1.5 ;
    v.y *= -1.;
    
    //this is a hack because the obj file was drawing upside down
    //gl_Position is read only...so pass to a temp variable and then change
    
    gl_Position = gl_ModelViewProjectionMatrix * v;
    
}
