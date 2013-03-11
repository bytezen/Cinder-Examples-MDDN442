#version 110


void main()
{
	vec4 v = vec4(gl_Vertex);
    v.z *= 0.0;
    v.y *= -1.;

    //this is a hack because the obj file was drawing upside down
    //gl_Position is read only...so pass to a temp variable and then change
    
    gl_Position = gl_ModelViewProjectionMatrix * v;
    
}
