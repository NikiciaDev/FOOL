#include <stdio.h>

#include "raylib.h"
#include "util/terrain/terrainutil.h"
#include "util/math/mathutil.h"
#include "util/random/randomutil.h"

int main() {
    const int screenWidth = 1920 / 2;
    const int screenHeight = 1080 / 2;

    InitWindow(screenWidth, screenHeight, "FOOL");

    int test_size = 512;
    int test[test_size];
    generate_terrain(test, test_size, 6, 1000, &cosip, 0.5f);
    for(int i = 0; i < 256; i++) {
       printf("%d\n", test[i]);
    }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello from raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
