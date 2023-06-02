#include "nextstep.h"
#include "raymath.h"
#include "collisioncalculation.h"

// PRIVATE
void collisionDetectionBadMethod(particle* particles, size_t number_of_particles) {
    for (size_t a = 0; a < number_of_particles; a++) {
        for (size_t b = a + 1; b < number_of_particles; b++) {
            if (doParticlesOverlap(particles[a], particles[b])) {
                Vector2 unitNormal = Vector2Subtract(particles[b].position, particles[a].position);
                unitNormal = Vector2Scale(unitNormal, 1./Vector2Length(unitNormal));
                Vector2 velocityAfter_a = velocityAfterTwoDimCollision(particles[a].mass, particles[b].mass, particles[a].velocity, particles[b].velocity, unitNormal);
                Vector2 velocityAfter_b = velocityAfterTwoDimCollision(particles[b].mass, particles[a].mass, particles[b].velocity, particles[a].velocity, unitNormal);
                particles[a].velocity = velocityAfter_a;
                particles[b].velocity = velocityAfter_b;
            }
        }
    }    
}


void nextStep(particle* particles, size_t number_of_particles, float deltaTime, Rectangle box) {

    // Particle to Particle Collision Detection and Correction
    
    // Create hash map

    // For each particle
    // Check the hash map for ajacent particles to compare to 

    
    collisionDetectionBadMethod(particles, number_of_particles);

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

    
    for (size_t a = 0; a < number_of_particles; a++) {
        for (size_t b = a + 1; b < number_of_particles; b++) {
            if (doParticlesOverlap(particles[a], particles[b])) {
                positionVelocityOverlapCorrectionWithTwoParticles(&particles[a], &particles[b]);
            }
        }
    }
    
    
}