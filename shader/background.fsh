#extension GL_OES_standard_derivatives : enable
precision highp float;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define NUM_EXPLOSIONS 1.
#define NUM_PARTICLES 30.
#define inv_nparticels (1./NUM_PARTICLES)
#define PI 3.1415926

float Hash11(float t){
    return fract(sin(t*613.2)*614.8);
}

vec2 Hash12(float t){
    return vec2(fract(sin(t*213.3)*314.8)-0.5,fract(sin(t*591.1)*647.2)-0.5);
}

vec2 Hash12_Polar(float t){
    float o = fract(sin(t*213.3)*314.8)*PI*2.0;
    float r = fract(sin(t*591.1)*647.2);
    return vec2(sin(o)*r,cos(o)*r);
}

float Noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);

    float a = Hash11(i.x + i.y * 57.0);
    float b = Hash11(i.x + 1.0 + i.y * 57.0);
    float c = Hash11(i.x + (i.y + 1.0) * 57.0);
    float d = Hash11(i.x + 1.0 + (i.y + 1.0) * 57.0);

    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);
}

float FBM(vec2 p, float t) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for(int i=0; i<4; i++) {
        value += amplitude * Noise(p * frequency + t * 0.1);
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

float Explosion(vec2 uv, float t)
{
    float fract_t = fract(t);
    float floor_t = floor(t);
    float power = 0.3 + Hash11(floor_t);
    float sparks = 0.0;

    for(float i=0.; i<NUM_PARTICLES; i++)
    {
        vec2 dir = Hash12_Polar(i * floor_t);
        float inv_d = 1.0 / (length(uv - dir * sqrt(fract_t)) + 0.001);
        float brightness = mix(0.3, 0.09, smoothstep(0., 0.1, fract_t)) *
        (1.0 - (0.5 + 0.5 * Hash11(i)) * fract_t);
        float sparkling = 0.5 + 0.5 * sin(t * 10.2 + floor_t * i);
        sparks += power * brightness * sparkling * inv_nparticels * inv_d;
    }
    return sparks;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;

    vec3 bgColor1 = vec3(0.02, 0.05, 0.15);
    vec3 bgColor2 = vec3(0.08, 0.02, 0.2);
    vec3 bgColor3 = vec3(0.05, 0.1, 0.25);

    float gradientMix = 0.5 + 0.5 * sin(time * 0.3);
    vec3 baseColor = mix(bgColor1, bgColor2, uv.y + 0.5);
    baseColor = mix(baseColor, bgColor3, gradientMix);

    float nebula = FBM(uv * 2.0, time * 0.2);
    vec3 nebulaColor = vec3(0.15, 0.05, 0.25) * nebula * 0.4;

    vec3 col = baseColor + nebulaColor;

    for(float i=0.; i<NUM_EXPLOSIONS; i++){
        float t = time * (0.3 + 0.4 * Hash11(i)) + i / NUM_EXPLOSIONS;
        float fract_t = fract(t);
        float floor_t = floor(t);

        float seed = floor_t + i * 7.13;
        vec3 color = 0.5 + 0.5 * vec3(
        Hash11(seed),
        Hash11(seed + 1.23),
        Hash11(seed + 2.71)
        );
        vec2 center = Hash12(i + 10. + 5. * floor_t);
        col += Explosion(uv - center, t) * color;
    }

    float vignette = 1.0 - length(uv) * 0.3;
    col *= vignette;

    gl_FragColor = vec4(col, 1.0);
}
