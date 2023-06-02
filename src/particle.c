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

void create2DHashMap(section* sections, size_t numberOfSections, float sectionWidth, particle* particles, Rectangle box, size_t number_of_particles) {
    // Reset sections
    for (size_t i = 0; i < numberOfSections; i++) {
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
    size_t sectionsInXDirection = ceil(box.width/sectionWidth);
    size_t sectionsInYDirection = ceil(box.height/sectionWidth);
    sectionIndexList sectionIndexes;

    if (currentSectionIndex == sectionsInXDirection*sectionsInYDirection - 1) {
        // In BR
        sectionIndexes.numberOfSections = 0;
        return sectionIndexes;
    }

    if (currentSectionIndex >= sectionsInXDirection*(sectionsInYDirection-1)) {
        // In B
        sectionIndexes.numberOfSections = 1;
        sectionIndexes.sectionIndex[0] = currentSectionIndex + 1; // R
        return sectionIndexes;
    }

    if (currentSectionIndex%sectionsInXDirection == 0) {
        // In L
        sectionIndexes.numberOfSections = 3;
        sectionIndexes.sectionIndex[0] = currentSectionIndex+1; // R
        sectionIndexes.sectionIndex[1] = currentSectionIndex+sectionsInXDirection; // D
        sectionIndexes.sectionIndex[2] = currentSectionIndex+sectionsInXDirection+1; // DR
        return sectionIndexes;
    }

    if ((currentSectionIndex+1)%sectionsInXDirection == 0) {
        // In R
        sectionIndexes.numberOfSections = 2;
        sectionIndexes.sectionIndex[0] = currentSectionIndex+sectionsInXDirection-1; // DL
        sectionIndexes.sectionIndex[1] = currentSectionIndex+sectionsInXDirection; // D
        return sectionIndexes;
    }

    // In center section
    sectionIndexes.numberOfSections = 4;
    sectionIndexes.sectionIndex[0] = currentSectionIndex+1; // R
    sectionIndexes.sectionIndex[1] = currentSectionIndex+sectionsInXDirection-1; // DL
    sectionIndexes.sectionIndex[2] = currentSectionIndex+sectionsInXDirection; // D
    sectionIndexes.sectionIndex[3] = currentSectionIndex+sectionsInXDirection+1; // DR
    return sectionIndexes;
}