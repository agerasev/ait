/*
attribute vec2 pos;
attribute vec2 tex;
uniform mat2 view;
*/

uniform float aspect; //screen aspect ratio
uniform float ang;

attribute vec2 vertex;
attribute vec3 color;
attribute vec2 texcoord;

void main(void)
{
    mat2 mat = mat2(cos(ang),sin(ang),-sin(ang),cos(ang));
    gl_Position = vec4(mat*vertex,0.0,1.0);
    gl_Position.x *= aspect;
    gl_FrontColor = vec4(color,1.0);
    gl_TexCoord[0] = vec4(texcoord,0.0,1.0);
}
