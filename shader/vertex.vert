#version 150

uniform mat2 projection;
uniform mat2 modelview;
uniform vec2 translation;

attribute vec2 coord;
attribute vec4 color;
attribute vec2 texcoord;

varying vec4 vcolor;
varying vec2 vtexcoord;

void main(void)
{
	gl_Position = vec4(projection*modelview*(coord + translation),0.0,1.0);
	vcolor      = color;
	vtexcoord   = texcoord;
}
