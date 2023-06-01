#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct particle
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    float mass;
    Color color;
} particle;

bool doParticlesOverlap(particle particle1, particle particle2);
float calculateKineticEnergy(particle* particles, size_t number_of_particles);

// N-body solutions part
enum {
    MAX_NUMBER_OF_PARTICLES_IN_SECTION = 200,
};

typedef struct section
{
    size_t numberOfParticles;
    particle* particles[MAX_NUMBER_OF_PARTICLES_IN_SECTION];
} section;

void create2DHashMap(section* sections, float sectionWidth, particle* particles, Rectangle box, size_t number_of_particles);

#endif // PARTICLE_H