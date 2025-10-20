#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D heightmap;
uniform int terrain_size;
uniform int max_height;
uniform float screenHeight;

void main() {
    float x = fragTexCoord.x;
    float y = fragTexCoord.y;

    // Sample height from texture
    float height = texture(heightmap, vec2(x, 0.0)).r;

    // Normalize height to screen space
    float terrain_y = 1.0 - (height / screenHeight);

    if(y > terrain_y) {
        finalColor = vec4(0.5, 0.8, 1.0, 1.0); // Sky
    } else {
        finalColor = vec4(0.4, 0.7, 0.2, 1.0); // Terrain
    }
}