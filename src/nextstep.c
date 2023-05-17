#include "nextstep.h"

void nextStep(particle* particles, size_t number_of_particles, float deltaTime, Rectangle box) {
    for (size_t i = 0; i < number_of_particles; i++)
    {
        // Detect and correct Collision
        if (particles[i].position.x + particles[i].radius > box.x + box.width || particles[i].position.x - particles[i].radius < box.x) {
            particles[i].velocity.x = -particles[i].velocity.x;
        }
        if (particles[i].position.y + particles[i].radius > box.y || particles[i].position.y - particles[i].radius < box.y - box.height) {
            particles[i].velocity.y = -particles[i].velocity.y;
        }

        // Add velocity to position
        particles[i].position.x += deltaTime*particles[i].velocity.x;
        particles[i].position.y += deltaTime*particles[i].velocity.y;

    }
}