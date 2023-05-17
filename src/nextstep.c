#include "nextstep.h"

void nextStep(particle* particles, size_t number_of_particles, float deltaTime) {
    for (size_t i = 0; i < number_of_particles; i++)
    {
        particles[i].position.x += deltaTime*particles[i].velocity.x;
        particles[i].position.y += deltaTime*particles[i].velocity.y;
    }
}