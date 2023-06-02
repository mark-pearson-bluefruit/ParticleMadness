#ifndef NEXTSTEP_H
#define NEXTSTEP_H

#include "particle.h"
#include <stdint.h>

void nextStep(particle* particles, size_t number_of_particles, float deltaTime, Rectangle box);
void collisionDetectionBadMethod(particle* particles, size_t number_of_particles); // PRIVATE

#endif // NEXTSTEP_H