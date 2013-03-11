#version 110


void main()
{
    gl_FrontColor = gl_Color;
	
	gl_Position = ftransform();
    
    //this is a hack because the obj file was drawing upside down
    //gl_Position is read only...so pass to a temp variable and then change
    vec4 p = gl_Position;
    p.y *= -1.0; 
    gl_Position = p;
}
