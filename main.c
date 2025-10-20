#include <stdio.h>

#include "raylib.h"
#include "raymath.h"
#include "util/terrain/terrainutil.h"
#include "util/math/mathutil.h"

int main(void) {
    const int screenWidth = 1920 / 2;
    const int screenHeight = 1080 / 2;
    InitWindow(screenWidth, screenHeight, "FOOL");

    const int TEST_SIZE = 64;
    int test[TEST_SIZE];
    generate_terrain(test, TEST_SIZE, 5, 500, &cosip, 0.5f);
    for(int i = 0; i < TEST_SIZE; i++) {
        printf("test[%d] = %d\n", i, test[i]);
    }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raw Terrain Visualization", 10, 10, 20, DARKGRAY);

        float xStep = (float)screenWidth / (TEST_SIZE - 1);

        // Fill the terrain with triangles from bottom of screen to terrain line
        for (int i = 0; i < TEST_SIZE - 1; i++) {
            Vector2 p1 = {i * xStep, test[i]};
            Vector2 p2 = {(i + 1) * xStep, test[i + 1]};
            Vector2 p3 = {(i + 1) * xStep, screenHeight};
            Vector2 p4 = {i * xStep, screenHeight};

            // Draw two triangles to form a quad
            DrawTriangle(p1, p3, p2, GREEN);
            DrawTriangle(p1, p4, p3, GREEN);
        }

        // Draw the outline on top
        for (int i = 0; i < TEST_SIZE - 1; i++) {
            Vector2 a = {i * xStep, test[i]};
            Vector2 b = {(i + 1) * xStep, test[i + 1]};
            DrawLineV(a, b, BLACK);
            DrawCircle(i * xStep, test[i], 2, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}