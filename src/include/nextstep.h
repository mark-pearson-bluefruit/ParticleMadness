#ifndef NEXTSTEP_H
#define NEXTSTEP_H

#include "particle.h"
#include <stdint.h>

void nextStep(particle* particles, size_t number_of_particles, float deltaTime);

#endif // NEXTSTEP_H