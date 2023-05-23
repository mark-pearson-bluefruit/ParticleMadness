#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <stdbool.h>

typedef struct particle
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    float mass;
    Color color;
} particle;

bool doParticlesOverlap(particle particle1, particle particle2);

#endif // PARTICLE_H