#include <stdio.h>

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
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FOOL");
    SetTargetFPS(240);

    RenderTexture2D target = LoadRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    // Load the background shader
    Shader bgShader = LoadShader(nullptr, "E:/Coding Projects/CLion/FOOL/shader/background.fsh");

    // Get shader uniform locations
    int timeLoc = GetShaderLocation(bgShader, "time");
    int resolutionLoc = GetShaderLocation(bgShader, "resolution");
    int mouseLoc = GetShaderLocation(bgShader, "mouse");

    float time = 0.0f;

    const int ARRAY_SIZE = 128;
    int terrain[ARRAY_SIZE];
    int heighest_point = 0;
    generate_terrain(terrain, ARRAY_SIZE, 7, 1000, &cosip, 0.5f, &heighest_point);
    printf("%d\n", heighest_point);

    Ball ball = create_ball(100, 0, 10, 0, 8, DEFAULT_BOUNCINESS);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        time += deltaTime;

        update_ball(&ball, terrain, ARRAY_SIZE, deltaTime);

        // Update shader uniforms
        SetShaderValue(bgShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        float resolution[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
        SetShaderValue(bgShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        Vector2 mousePos = GetMousePosition();
        float mouse[2] = { mousePos.x, mousePos.y };
        SetShaderValue(bgShader, mouseLoc, mouse, SHADER_UNIFORM_VEC2);

        BeginTextureMode(target);
        ClearBackground(BLACK);
        BeginShaderMode(bgShader);
        DrawRectangle(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT, WHITE);
        EndShaderMode();

        draw_terrain(terrain, ARRAY_SIZE, true);
        draw_ball(&ball);

        EndTextureMode();

        BeginDrawing();

        // Draw shader background


        // Draw game content on top
        float scaleX = (float)GetScreenWidth() / TEXTURE_WIDTH;
        float scaleY = (float)GetScreenHeight() / TEXTURE_HEIGHT;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;

        int scaled_width = (int)(TEXTURE_WIDTH * scale);
        int scaled_height = (int)(TEXTURE_HEIGHT * scale);
        int offset_x = (GetScreenWidth() - scaled_width) / 2;
        int offset_y = (GetScreenHeight() - scaled_height) / 2;

        Rectangle src = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
        Rectangle dest = { (float)offset_x, (float)offset_y, (float)scaled_width, (float)scaled_height };

        DrawTexturePro(target.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadShader(bgShader);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}