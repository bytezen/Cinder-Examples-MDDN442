#version 110

uniform vec2 nmouse;

void main()
{    
    gl_FragColor.rgba = vec4(nmouse, 0.4,1.0); 
//    gl_FragColor.rgba = vec4(nmouse.x, nmouse.y, 0.4,1.0);     
}
