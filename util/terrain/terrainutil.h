//
// Created by LRieh on 19/10/2025.
//

#ifndef FOOL_WORLD_H
#define FOOL_WORLD_H

//https://arpitbhayani.me/blogs/1d-terrain/

void generate_terrain(int* height_map, int height_map_size, int samples, int max_height, float (*interpolator)(float, float, float), float mu);

void draw_terrain(int* height_map, int height_map_size, int screen_width, int screen_height, bool debug);

#endif //FOOL_WORLD_H