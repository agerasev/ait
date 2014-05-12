attribute vec2 pos;
attribute vec2 tex;
uniform mat2 view;

void main(void)
{
    gl_Position = vec4(view*pos,0.0,1.0);
    gl_TexCoord[0] = vec4(tex,0.0,1.0);
}
