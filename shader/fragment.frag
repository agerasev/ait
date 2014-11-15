#version 150

uniform sampler2D texture;

varying vec4 vcolor;
varying vec2 vtexcoord;

void main(void)
{
	vec2 tbf = textureSize(texture,0)*vec2(0.5,1.0);
	vec2 qc, tc = vtexcoord*tbf;
	qc = vec2(floor(tc.x), floor(tc.y));
	qc.x += floor((tc.x + tc.y) - (qc.y + qc.x))/2.0;
	qc += vec2(0.25,0.5);
	qc /= tbf;
	gl_FragColor = vcolor * texture2D(texture, qc);
}
