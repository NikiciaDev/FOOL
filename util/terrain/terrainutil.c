//
// Created by LRieh on 19/10/2025.
//

#include "terrainutil.h"
#include "../random/randomutil.h"
#include "raylib.h"
#include "../../globals.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../math/mathutil.h"

void generate_terrain(int* terrain, int terrain_size, int samples, int max_height, float (*interpolator)(float, float, float), float mu) {
    memset(terrain, 0, sizeof(int) * terrain_size);
    printf("Generating terrain...\n");

    for(int i = 0; i < samples; i++) {
        short pow2 = pow(2, i);
        if(i == 0) pow2 = 1;

        for(int j = 0; j < terrain_size / pow2; j++) {
            int rand = (1.f / pow(2, samples - i)) * rand_int(0, max_height);

            for(int k = 0; k < pow2; k++) {
                if(j * pow2 + k >= terrain_size) break;
                terrain[j * pow2 + k] += rand;
            }
        }
    }

    for(int i = 1; i < terrain_size - 1; i++) {
        terrain[i] = interpolator(terrain[i - 1], terrain[i + 1], mu);
    }

    float actual_max = 0;
    for(int i = 0; i < terrain_size; i++) {
        if(terrain[i] > actual_max) actual_max = terrain[i];
    }

    for(int i = 0; i < terrain_size; i++) {
        terrain[i] = (terrain[i] / actual_max) * max_height;
    }
}

void draw_terrain(int* terrain, int terrain_size, bool debug) {
    float xStep = (float)TEXTURE_WIDTH / (terrain_size - 1);

    for (int i = 0; i < terrain_size - 1; i++) {
        Vector2 p1 = {i * xStep, terrain[i]};
        Vector2 p2 = {(i + 1) * xStep, terrain[i + 1]};
        Vector2 p3 = {(i + 1) * xStep, TEXTURE_HEIGHT};
        Vector2 p4 = {i * xStep, TEXTURE_HEIGHT};

        DrawTriangle(p1, p3, p2, GREEN);
        DrawTriangle(p1, p4, p3, GREEN);
    }

    for (int i = 0; i < terrain_size - 1; i++) {
        Vector2 a = {i * xStep, terrain[i]};
        Vector2 b = {(i + 1) * xStep, terrain[i + 1]};
        DrawLineV(a, b, BLACK);

        if(debug) DrawCircle(i * xStep, terrain[i], 4, RED);
    }
}

float get_terrain_height_at(int* terrain, int terrain_size, float x) {
    float x_step = (float)TEXTURE_WIDTH / (terrain_size - 1);
    int segment = x / x_step;

    if (segment < 0) segment = 0;
    if (segment >= terrain_size - 1) segment = terrain_size - 2;

    float x1 = segment * x_step;
    float x2 = (segment + 1) * x_step;
    float y1 = terrain[segment];
    float y2 = terrain[segment + 1];

    return lerp(x, x1, y1, x2, y2);
}

Vector2 get_terrain_normal_at(int* terrain, int terrain_size, float x) {
    float x_step = (float)TEXTURE_WIDTH / (terrain_size - 1);
    int segment = x / x_step;

    if (segment < 0) segment = 0;
    if (segment >= terrain_size - 1) segment = terrain_size - 2;

    float x1 = segment * x_step;
    float x2 = (segment + 1) * x_step;
    float y1 = terrain[segment];
    float y2 = terrain[segment + 1];

    Vector2 tangent = {x2 - x1, y2 - y1};
    float length = sqrt(tangent.x * tangent.x + tangent.y * tangent.y);
    tangent.x /= length;
    tangent.y /= length;

    Vector2 normal = {-tangent.y, tangent.x};

    return normal;
}