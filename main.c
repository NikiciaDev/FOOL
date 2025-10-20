#include <stdio.h>

#include "raylib.h"
#include "raymath.h"
#include "util/terrain/terrainutil.h"
#include "util/math/mathutil.h"

/*
TODO
What I tend to do is have a 1920 x 1080 render texture target that I render everything to,
then last thing before the end of the frame is to draw the render target to the screen,
scaled so it fits letterbox style (see the letterbox example in raylib)
*/

int main() {
    int screen_width = 1920 / 2;
    int screen_height = 1080 / 2;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "FOOL");

    const int TEST_SIZE = 128;
    int test[TEST_SIZE];
    generate_terrain(test, TEST_SIZE, 7, 500, &cosip, 0.5f);
    for(int i = 0; i < TEST_SIZE; i++) {
        printf("test[%d] = %d\n", i, test[i]);
    }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raw Terrain Visualization", 10, 10, 20, DARKGRAY);

        draw_terrain(test, TEST_SIZE, screen_width, screen_height, false);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}