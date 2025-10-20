//
// Created by LRieh on 20/10/2025.
//

#include "ball.h"
#include "raylib.h"
#include "../../globals.h"
#include "../../util/terrain/terrainutil.h"

Ball create_ball(float x, float y, float vx, float vy, float radius, float mass, float elasticity) {
    Ball ball;
    ball.x = x;
    ball.y = y;
    ball.vx = vx;
    ball.vy = vy;
    ball.radius = radius;
    ball.mass = mass;
    ball.bounciness = elasticity;

    ball.draw = &draw_ball;
    return ball;
}

void update_ball(Ball* ball, int* terrain, int terrain_size, float delta_time) {
    ball->vy += G;

    ball->x += ball->vx * delta_time;
    ball->y += ball->vy * delta_time;

    float terrain_height = get_terrain_height_at(terrain, terrain_size, ball->x);
    if(ball->y + ball->radius >= terrain_height) {
        ball->y = terrain_height - ball->radius;

        Vector2 normal = get_terrain_normal_at(terrain, terrain_size, ball->x);
        float vel_dot_normal = ball->vx * normal.x + ball->vy * normal.y;

        if(vel_dot_normal > 0.0f) {
            ball->vx -= (1 + ball->bounciness) * vel_dot_normal * normal.x;
            ball->vy -= (1 + ball->bounciness) * vel_dot_normal * normal.y;

            Vector2 tangent = {normal.y, -normal.x};
            float vel_dot_tangent = ball->vx * tangent.x + ball->vy * tangent.y;
            ball->vx -= FRICTION * vel_dot_tangent * tangent.x;
            ball->vy -= FRICTION * vel_dot_tangent * tangent.y;
        }
    }
}

void draw_ball(Ball* ball) {
    DrawCircle(ball->x, ball->y, ball->radius, WHITE);
}