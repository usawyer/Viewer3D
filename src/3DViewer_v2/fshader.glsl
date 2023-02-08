#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec4 colorl;

void main()
{
    gl_FragColor = colorl;
}
