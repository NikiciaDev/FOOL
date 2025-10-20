#include "raylib.h"
#include "globals.h"
#include "util/math/mathutil.h"
#include "util/terrain/terrainutil.h"
#include "entity/base/ball.h"

int main()
{
    const int WINDOW_WIDTH = 1920 / 2;
    const int WINDOW_HEIGHT = 1080 / 2;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FOOL");
    SetTargetFPS(240);

    RenderTexture2D target = LoadRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    const int ARRAY_SIZE = 24;
    int terrain[ARRAY_SIZE];
    generate_terrain(terrain, ARRAY_SIZE, 3, 900, &cosip, 0.5f);

    Ball ball = create_ball(100, 0, 10, 0, 8, DEFAULT_BOUNCINESS);

    while (!WindowShouldClose())
    {
        update_ball(&ball, terrain, ARRAY_SIZE, GetFrameTime());

        BeginTextureMode(target);
        ClearBackground(DARKBLUE);

        draw_terrain(terrain, ARRAY_SIZE, true);
        draw_ball(&ball);


        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        float scaleX = (float)GetScreenWidth() / TEXTURE_WIDTH;
        float scaleY = (float)GetScreenHeight() / TEXTURE_HEIGHT;
        float scale = (scaleX < scaleY) ? scaleX : scaleY; // Maintain aspect ratio

        int scaled_width = (int)(TEXTURE_WIDTH * scale);
        int scaled_height = (int)(TEXTURE_HEIGHT * scale);
        int offset_x = (GetScreenWidth() - scaled_width) / 2;
        int offset_y = (GetScreenHeight() - scaled_height) / 2;

        // Flip vertically cuz opengl weird
        Rectangle src = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
        Rectangle dest = { (float)offset_x, (float)offset_y, (float)scaled_width, (float)scaled_height };

        DrawTexturePro(target.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
