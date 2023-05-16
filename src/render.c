#include "render.h"
void displayParticle(particle* particles)
{
    (void) particles;
    DrawCircle(0, 0, 1., MAROON);
    DrawCircle(10, 15, 3., RED);
    DrawCircle(35, 35, 5., BLACK);
}