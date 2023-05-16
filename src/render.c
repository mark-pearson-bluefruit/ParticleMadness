#include "render.h"
void displayParticle(particle* particles, size_t number_of_particles)
{
    for (size_t i = 0; i < number_of_particles; i++)
    {
        DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, particles[i].color);
    }
}