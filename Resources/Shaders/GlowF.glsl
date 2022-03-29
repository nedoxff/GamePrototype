#version 330

uniform sampler2D texture;
uniform float bloom_spread = 1;
uniform float bloom_intensity = 2;

void main() {
    ivec2 size = textureSize(texture, 0);
    float uv_x = gl_TexCoord[0].x * size.x;
    float uv_y = gl_TexCoord[0].y * size.y;

    vec4 sum = vec4(0.0);
    for (int n = 0; n < 9; ++n) {
        uv_y = (gl_TexCoord[0].y * size.y) + (bloom_spread * float(n - 4));
        vec4 h_sum = vec4(0.0);
        h_sum += texelFetch(texture, ivec2(uv_x - (4.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x - (3.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x - (2.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x - bloom_spread, uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x, uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x + bloom_spread, uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x + (2.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x + (3.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(texture, ivec2(uv_x + (4.0 * bloom_spread), uv_y), 0);
        sum += h_sum / 9.0;
    }

    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) - ((sum / 9.0) * bloom_intensity);
}
