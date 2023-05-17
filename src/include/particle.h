#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct particle
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} particle;

#endif // PARTICLE_H