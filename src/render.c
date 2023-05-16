#include "render.h"
void displayParticle(particle* particles, size_t number_of_particles, Rectangle window, Vector2 resolution)
{
    // Not for circles to appear correct size must have
    // res.x/windowwidth = res.y/windowheight
    for (size_t i = 0; i < number_of_particles; i++)
    {
        int positionX = resolution.x*(particles[i].position.x-window.x)/window.width;
        int positionY = resolution.y - resolution.y*(particles[i].position.y-window.y+window.height)/window.height - 1;
        float radius = resolution.x*particles[i].radius/window.width;
        DrawCircle(positionX, positionY, radius, particles[i].color);
    }
}