#include "particle.h"
#include "raymath.h"

bool doParticlesOverlap(particle particle1, particle particle2) {
    Vector2 direction = Vector2Subtract(particle1.position,  particle2.position);
    float distanceSquared = Vector2DotProduct(direction, direction);
    float radiusSquared = (particle1.radius + particle2.radius)*(particle1.radius + particle2.radius);
    return (distanceSquared < radiusSquared);
}

float calculateKineticEnergy(particle* particles, size_t number_of_particles) {
    float totalEnergy = 0.;
    for (size_t i = 0; i < number_of_particles; i++) {
        totalEnergy += (particles[i].mass*Vector2DotProduct(particles[i].velocity, particles[i].velocity))/2.;
    }
    return totalEnergy;
}
