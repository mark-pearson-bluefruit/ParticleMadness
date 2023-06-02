#include "particle.h"
#include "raymath.h"
#include <math.h>

bool doParticlesOverlap(particle particle1, particle particle2) {
    Vector2 direction = Vector2Subtract(particle1.position,  particle2.position);
    float distanceSquared = Vector2DotProduct(direction, direction);
    float radiusSquared = (particle1.radius + particle2.radius)*(particle1.radius + particle2.radius);
    return (distanceSquared <= radiusSquared);
}

float calculateKineticEnergy(particle* particles, size_t number_of_particles) {
    float totalEnergy = 0.;
    for (size_t i = 0; i < number_of_particles; i++) {
        totalEnergy += (particles[i].mass*Vector2DotProduct(particles[i].velocity, particles[i].velocity))/2.;
    }
    return totalEnergy;
}

void create2DHashMap(section* sections, float sectionWidth, particle* particles, Rectangle box, size_t number_of_particles) {
    // Reset sections
    for (size_t i = 0; i < 130; i++) {
        sections[i].numberOfParticles = 0;
    }


    size_t sectionsInXDirection = ceil(box.width/sectionWidth);
    size_t sectionsInYDirection = ceil(box.height/sectionWidth);

    for (size_t i = 0; i < number_of_particles; i++) {
        size_t xSectionPosition = (particles[i].position.x - box.x)/sectionWidth;
        size_t ySectionPosition = (particles[i].position.y - (box.y - box.height))/sectionWidth;
        size_t sectionIndex = xSectionPosition + ySectionPosition*sectionsInXDirection;
        sections[sectionIndex].particles[sections[sectionIndex].numberOfParticles] = &particles[i];
        sections[sectionIndex].numberOfParticles++;
    }
}

sectionIndexList getSectionsToCheck(size_t currentSectionIndex, float sectionWidth, Rectangle box) {
    sectionIndexList sectionIndexes;
    sectionIndexes.numberOfSections = 3;
    sectionIndexes.sectionIndex[0] = 1;
    sectionIndexes.sectionIndex[1] = 5;
    sectionIndexes.sectionIndex[2] = 6;
    return sectionIndexes;
}