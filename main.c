#include "raylib.h"
#include "globals.h"
#include "util/math/mathutil.h"
#include "util/terrain/terrainutil.h"

int main()
{
    const int WINDOW_WIDTH = 1920 / 2;
    const int WINDOW_HEIGHT = 1080 / 2;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FOOL");

    RenderTexture2D target = LoadRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    SetTargetFPS(60);

    const int ARRAY_SIZE = 256;
    int terrain[ARRAY_SIZE];
    generate_terrain(terrain, ARRAY_SIZE, 10, 900, &cosip, 0.5f);
    while (!WindowShouldClose())
    {
        BeginTextureMode(target);
        ClearBackground(DARKBLUE);

        draw_terrain(terrain, ARRAY_SIZE, true);

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        float scaleX = (float)GetScreenWidth() / TEXTURE_WIDTH;
        float scaleY = (float)GetScreenHeight() / TEXTURE_HEIGHT;
        float scale = (scaleX < scaleY) ? scaleX : scaleY; // Maintain aspect ratio

        int scaledWidth = (int)(TEXTURE_WIDTH * scale);
        int scaledHeight = (int)(TEXTURE_HEIGHT * scale);
        int offsetX = (GetScreenWidth() - scaledWidth) / 2;
        int offsetY = (GetScreenHeight() - scaledHeight) / 2;

        // Flip vertically cuz opengl weird
        Rectangle src = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
        Rectangle dest = { (float)offsetX, (float)offsetY, (float)scaledWidth, (float)scaledHeight };

        DrawTexturePro(target.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
