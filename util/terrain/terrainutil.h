//
// Created by LRieh on 19/10/2025.
//

#ifndef FOOL_TERRAINUTIL_H
#define FOOL_TERRAINUTIL_H
#include "raylib.h"

//https://arpitbhayani.me/blogs/1d-terrain/

void generate_terrain(int* terrain, int terrain_size, int samples, int max_height, float (*interpolator)(float, float, float), float mu, int* heighest_terrain_height);

void draw_terrain(int* terrain, int terrain_size, bool debug);

float get_terrain_height_at(int* terrain, int terrain_size, float x);

Vector2 get_terrain_normal_at(int* terrain, int terrain_size, float x);

#endif //FOOL_TERRAINUTIL_H