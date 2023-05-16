#ifndef RENDER_H
#define RENDER_H

#include "particle.h"
#include <stdint.h>

void displayParticle(particle* particles, size_t number_of_particles, Rectangle window, Vector2 resolution);

#endif // RENDER_H