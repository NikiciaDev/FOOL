#include <stdio.h>
#include "raylib.h"
#include "globals.h"
#include "util/math/mathutil.h"
#include "util/terrain/terrainutil.h"
#include "entity/base/ball.h"

#define WINDOW_WIDTH  (1920 / 2)
#define WINDOW_HEIGHT (1080 / 2)

static void InitGame(RenderTexture2D *target, Shader *bgShader,
                     int *timeLoc, int *resolutionLoc, int *mouseLoc);
static void UpdateGame(float *time, Shader bgShader, int timeLoc, int resolutionLoc, int mouseLoc,
                       Ball *ball, int *terrain, float deltaTime);
static void DrawGame(RenderTexture2D target, Ball ball, int *terrain, Shader bgShader);
static void CleanupGame(RenderTexture2D target, Shader bgShader);

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FOOL");
    SetTargetFPS(240);

    RenderTexture2D target;
    Shader bgShader;
    int timeLoc, resolutionLoc, mouseLoc;

    InitGame(&target, &bgShader, &timeLoc, &resolutionLoc, &mouseLoc);

    // Terrain + Entities
    int ARRAY_SIZE = 128;
    int terrain[ARRAY_SIZE];
    int highest_point = 0;
    generate_terrain(terrain, ARRAY_SIZE, 7, 1000, &cosip, 0.5f, &highest_point);
    printf("Highest point: %d\n", highest_point);

    Ball ball = create_ball(100, 0, 10, 0, 8, DEFAULT_BOUNCINESS);

    float time = 0.0f;
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        time += deltaTime;

        update_ball(&ball, terrain, ARRAY_SIZE, deltaTime);
        UpdateGame(&time, bgShader, timeLoc, resolutionLoc, mouseLoc, &ball, terrain, deltaTime);
        DrawGame(target, ball, terrain, bgShader);
    }

    CleanupGame(target, bgShader);
    CloseWindow();

    return 0;
}

// Initialize render targets, shaders, etc.
static void InitGame(RenderTexture2D *target, Shader *bgShader,
                     int *timeLoc, int *resolutionLoc, int *mouseLoc)
{
    *target = LoadRenderTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    SetTextureFilter(target->texture, TEXTURE_FILTER_BILINEAR);

    *bgShader = LoadShader(NULL, "E:/Coding Projects/CLion/FOOL/shader/background.fsh");
    *timeLoc = GetShaderLocation(*bgShader, "time");
    *resolutionLoc = GetShaderLocation(*bgShader, "resolution");
    *mouseLoc = GetShaderLocation(*bgShader, "mouse");
}

// Update shader uniforms, entities, etc.
static void UpdateGame(float *time, Shader bgShader, int timeLoc, int resolutionLoc, int mouseLoc,
                       Ball *ball, int *terrain, float deltaTime)
{
    SetShaderValue(bgShader, timeLoc, time, SHADER_UNIFORM_FLOAT);

    float resolution[2] = { (float)TEXTURE_WIDTH, (float)TEXTURE_HEIGHT };
    SetShaderValue(bgShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    Vector2 mousePos = GetMousePosition();
    float mouse[2] = { mousePos.x, mousePos.y };
    SetShaderValue(bgShader, mouseLoc, mouse, SHADER_UNIFORM_VEC2);
}

// Draw everything
static void DrawGame(RenderTexture2D target, Ball ball, int *terrain, Shader bgShader)
{
    // Render to texture
    BeginTextureMode(target);
        ClearBackground(BLACK);
        BeginShaderMode(bgShader);
        DrawRectangle(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT, WHITE);
        EndShaderMode();

        draw_terrain(terrain, 128, true); // TEMP TERRAIN SIZE IS NOT ACCURATE
        draw_ball(&ball);
    EndTextureMode();

    // Render texture to screen (scaled)
    BeginDrawing();
        float scaleX = (float)GetScreenWidth() / TEXTURE_WIDTH;
        float scaleY = (float)GetScreenHeight() / TEXTURE_HEIGHT;
        float scale = (scaleX < scaleY) ? scaleX : scaleY;

        int scaledW = (int)(TEXTURE_WIDTH * scale);
        int scaledH = (int)(TEXTURE_HEIGHT * scale);
        int offsetX = (GetScreenWidth() - scaledW) / 2;
        int offsetY = (GetScreenHeight() - scaledH) / 2;

        Rectangle src = { 0, 0, (float)target.texture.width, -(float)target.texture.height };
        Rectangle dest = { (float)offsetX, (float)offsetY, (float)scaledW, (float)scaledH };
        DrawTexturePro(target.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
    EndDrawing();
}

// Cleanup assets
static void CleanupGame(RenderTexture2D target, Shader bgShader)
{
    UnloadShader(bgShader);
    UnloadRenderTexture(target);
}
