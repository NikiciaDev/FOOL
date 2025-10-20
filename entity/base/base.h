//
// Created by LRieh on 20/10/2025.
//

#ifndef FOOL_BASE_H
#define FOOL_BASE_H

typedef struct {
    float x, y;
    float vx, vy;
    float radius;
    float mass;
    float elasticity;
} Ball;

Ball createBall(float x, float y, float vx, float vy, float radius, float mass, float elasticity);

typedef struct {
    float x, y;
    float width, height;
} Rect;

Rect createRect(float x, float y, float width, float height);

#endif //FOOL_BASE_H