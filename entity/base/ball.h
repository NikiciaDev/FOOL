//
// Created by LRieh on 20/10/2025.
//

#ifndef FOOL_BALL_H
#define FOOL_BALL_H

extern const float DEFAULT_BOUNCINESS;

typedef struct Ball {
    float x, y;
    float vx, vy;
    float radius;
    float bounciness;

    void (*draw)(struct Ball*);
} Ball;

Ball create_ball(float x, float y, float vx, float vy, float radius, float bounciness);

void update_ball(Ball* ball, int* terrain, int terrain_size, float delta_time);

void draw_ball(Ball* self);

#endif //FOOL_BALL_H