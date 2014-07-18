uniform sampler2D texture;

const int TS = 16;
const vec2 TS2 = vec2(TS,TS);

void main(void)
{
    vec2 qc, tc = gl_TexCoord[0].xy*TS2;
    qc = vec2(floor(tc.x), floor(tc.y));
    qc.x += floor((tc.x + tc.y) - (qc.y + qc.x))/2.0;
    qc += vec2(0.25,0.5);
    qc /= TS2;
    gl_FragColor = gl_Color * texture2D(texture, qc);
}
