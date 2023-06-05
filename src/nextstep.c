#include "nextstep.h"
#include "raymath.h"
#include "collisioncalculation.h"

static section sections[MAX_NUMBER_OF_SECTIONS];

void collisionResponse(particle* particle1, particle* particle2) {
    if (doParticlesOverlap(*particle1, *particle2)) {
        Vector2 unitNormal = Vector2Subtract(particle2->position, particle1->position);
        unitNormal = Vector2Scale(unitNormal, 1./Vector2Length(unitNormal));
        Vector2 velocityAfter_a = velocityAfterTwoDimCollision(particle1->mass, particle2->mass, particle1->velocity, particle2->velocity, unitNormal);
        Vector2 velocityAfter_b = velocityAfterTwoDimCollision(particle2->mass, particle1->mass, particle2->velocity, particle1->velocity, unitNormal);
        particle1->velocity = velocityAfter_a;
        particle2->velocity = velocityAfter_b;
    }    
}

// PRIVATE
void collisionDetectionBadMethod(particle* particles, size_t number_of_particles, Rectangle box) {
    for (size_t a = 0; a < number_of_particles; a++) {
        for (size_t b = a + 1; b < number_of_particles; b++) {
            collisionResponse(&particles[a], &particles[b]);
        }
    }    
}

// PRIVATE
void collisionDetectionHashMap(particle* particles, size_t number_of_particles, Rectangle box) {
    // Create hash map 
    
    const float sectionWidth = 3.;
    // Section width is set to biggest radius
    
    create2DHashMap(sections, sectionWidth, particles, box, number_of_particles);
    
    size_t sectionsInXDirection = ceil(box.width/sectionWidth);
    size_t sectionsInYDirection = ceil(box.height/sectionWidth);

    size_t numberOfSections = sectionsInXDirection*sectionsInYDirection;

    for (size_t sectionIndex = 0; sectionIndex < numberOfSections; sectionIndex++) {
        
        sectionIndexList neighbourSections = getSectionsToCheck(sectionIndex, sectionWidth, box);
        for (size_t particleIndex = 0; particleIndex < sections[sectionIndex].numberOfParticles; particleIndex++) {

            // Compare with particles in neighbouring sections
            for (size_t compareSectionLoop = 0; compareSectionLoop < neighbourSections.numberOfSections; compareSectionLoop++) {
                for (size_t particleCompareIndex = 0; particleCompareIndex < sections[neighbourSections.sectionIndex[compareSectionLoop]].numberOfParticles; particleCompareIndex++) {
                    collisionResponse(sections[sectionIndex].particles[particleIndex], sections[neighbourSections.sectionIndex[compareSectionLoop]].particles[particleCompareIndex]);
                }
            }

            // Compare with other particles in this section
            for (size_t particleIndexB = particleIndex + 1; particleIndexB < sections[sectionIndex].numberOfParticles; particleIndexB++) {
                collisionResponse(sections[sectionIndex].particles[particleIndex], sections[sectionIndex].particles[particleIndexB]);
            }
        }
    }

    // does not take into account particles in current box
    
    // For all sections
        // Get particles in section
        // Get particles in next door section
        // For each particle in this section
            // For each particle in the next door section

}

void positionVelocityOverlapCorrectionBadMethod(particle* particles, size_t number_of_particles, Rectangle box) {
    for (size_t a = 0; a < number_of_particles; a++) {
        for (size_t b = a + 1; b < number_of_particles; b++) {
            if (doParticlesOverlap(particles[a], particles[b])) {
                positionVelocityOverlapCorrectionWithTwoParticles(&particles[a], &particles[b]);
            }
        }
    }    
}

void positionVelocityOverlapCorrectionHashMethod(particle* particles, size_t number_of_particles, Rectangle box) {
    // Create hash map 
    
    const float sectionWidth = 3.;
    // Section width is set to biggest radius
    
    create2DHashMap(sections, sectionWidth, particles, box, number_of_particles);
    
    size_t sectionsInXDirection = ceil(box.width/sectionWidth);
    size_t sectionsInYDirection = ceil(box.height/sectionWidth);

    size_t numberOfSections = sectionsInXDirection*sectionsInYDirection;

    for (size_t sectionIndex = 0; sectionIndex < numberOfSections; sectionIndex++) {
        
        sectionIndexList neighbourSections = getSectionsToCheck(sectionIndex, sectionWidth, box);
        for (size_t particleIndex = 0; particleIndex < sections[sectionIndex].numberOfParticles; particleIndex++) {

            // Compare with particles in neighbouring sections
            for (size_t compareSectionLoop = 0; compareSectionLoop < neighbourSections.numberOfSections; compareSectionLoop++) {
                for (size_t particleCompareIndex = 0; particleCompareIndex < sections[neighbourSections.sectionIndex[compareSectionLoop]].numberOfParticles; particleCompareIndex++) {
                    positionVelocityOverlapCorrectionWithTwoParticles(sections[sectionIndex].particles[particleIndex], sections[neighbourSections.sectionIndex[compareSectionLoop]].particles[particleCompareIndex]);
                }
            }

            // Compare with other particles in this section
            for (size_t particleIndexB = particleIndex + 1; particleIndexB < sections[sectionIndex].numberOfParticles; particleIndexB++) {
                positionVelocityOverlapCorrectionWithTwoParticles(sections[sectionIndex].particles[particleIndex], sections[sectionIndex].particles[particleIndexB]);
            }
        }
    }
}

void nextStep(particle* particles, size_t number_of_particles, float deltaTime, Rectangle box) {

    // Particle to Particle Collision Detection and Correction
    
    // Create hash map

    // For each particle
    // Check the hash map for ajacent particles to compare to 

    
    collisionDetectionHashMap(particles, number_of_particles, box);

    for (size_t i = 0; i < number_of_particles; i++)
    {
        // Detect and correct Collision

        // Bounding Box Detection And Correction
        /*
        if (particles[i].position.x + particles[i].radius > box.x + box.width || particles[i].position.x - particles[i].radius < box.x) {
            particles[i].velocity.x = -particles[i].velocity.x;
        }
        if (particles[i].position.y + particles[i].radius > box.y || particles[i].position.y - particles[i].radius < box.y - box.height) {
            particles[i].velocity.y = -particles[i].velocity.y;
        }
        */

        // Add velocity to position
        particles[i].position.x += deltaTime*particles[i].velocity.x;
        particles[i].position.y += deltaTime*particles[i].velocity.y;

        positionVelocityCorrectionWithBoundingBox(&particles[i], box);

    }

    positionVelocityOverlapCorrectionHashMethod(particles, number_of_particles, box);
    /*
    for (size_t a = 0; a < number_of_particles; a++) {
        for (size_t b = a + 1; b < number_of_particles; b++) {
            if (doParticlesOverlap(particles[a], particles[b])) {
                positionVelocityOverlapCorrectionWithTwoParticles(&particles[a], &particles[b]);
            }
        }
    }
    */
    
    
}