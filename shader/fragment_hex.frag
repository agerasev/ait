#version 150

uniform sampler2D texture;
uniform sampler2D tiles;

varying vec4 vcolor;
varying vec2 vtexcoord;

void main(void)
{
	gl_FragColor = vcolor * texture2D(texture, vtexcoord);
}
