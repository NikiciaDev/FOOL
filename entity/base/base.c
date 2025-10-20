//
// Created by LRieh on 20/10/2025.
//

#include "base.h"
#include "../../globals.h"

Ball createBall(float x, float y, float vx, float vy, float radius, float mass, float elasticity) {
    Ball ball;
    ball.x = x;
    ball.y = y;
    ball.vx = vx;
    ball.vy = vy;
    ball.radius = radius;
    ball.mass = mass;
    ball.bounciness = elasticity;
    ball.update = update;

    return ball;
}

void update() {

}

Rect createRect(float x, float y, float width, float height) {
    Rect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    return rect;
}