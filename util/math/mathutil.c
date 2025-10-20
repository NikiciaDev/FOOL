//
// Created by LRieh on 19/10/2025.
//

#include "mathutil.h"
#include <math.h>

#define PI 3.14159265358979323846f

float linip(float a, float b, float mu) {
    return a * (1 - mu) + b * mu;
}

float cosip(float a, float b, float mu) {
    float mu2 = (1 - cosf(mu * PI)) / 2;
    return a * (1 - mu2) + b * mu2;
}

float smoip(float a, float b, float mu) {
    mu = mu * mu * (3 - 2 * mu);
    return a * (1 - mu) + b * mu;
}

float lerp(float x, float x1, float y1, float x2, float y2) {
    return  y1 + ((x - x1) * (y2 - y1)) / (x2 - x1);
}
