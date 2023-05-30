#include "particle.h"
#include "raymath.h"

bool doParticlesOverlap(particle particle1, particle particle2) {
    Vector2 direction = Vector2Subtract(particle1.position,  particle2.position);
    float distanceSquared = Vector2DotProduct(direction, direction);
    float radiusSquared = (particle1.radius + particle2.radius)*(particle1.radius + particle2.radius);
    return (distanceSquared < radiusSquared);
}