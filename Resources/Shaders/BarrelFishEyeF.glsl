#version 330

uniform sampler2D texture;
uniform float power;

vec2 Distort(vec2 p)
{
    float theta  = atan(p.y, p.x);
    float radius = length(p);
    radius = pow(radius, power);
    p.x = radius * cos(theta);
    p.y = radius * sin(theta);
    return 0.5 * (p + 1.0);
}

void main()
{
    vec2 xy = 2.0 * gl_TexCoord[0].xy - 1.0;
    vec2 uv;
    float d = length(xy);
    if (d < 1.0)
    {
        uv = Distort(xy);
    }
    else
    {
        uv = gl_TexCoord[0].xy;
    }
    vec4 c = texture2D(texture, uv);
    gl_FragColor = c;
}