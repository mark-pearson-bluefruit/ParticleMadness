#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

struct particle
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

#endif // PARTICLE_H