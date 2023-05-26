#include "collisioncalculation.h"
#include "raymath.h"

float velocityAfterOneDimCollision(float mass1, float mass2, float velocityBefore1, float velocityBefore2) {
    return ((mass1 - mass2)*velocityBefore1 + 2.*mass2*velocityBefore2)/(mass1 + mass2);
}

Vector2 velocityAfterTwoDimCollision(float mass1, float mass2, Vector2 velocityBefore1, Vector2 velocityBefore2, Vector2 unitNormal) {
    float velocityBeforeInUnitNormal1 = Vector2DotProduct(velocityBefore1, unitNormal);
    float velocityBeforeInUnitNormal2 = Vector2DotProduct(velocityBefore2, unitNormal);
    float velocityAfterInUnitNormal1 = velocityAfterOneDimCollision(mass1, mass2, velocityBeforeInUnitNormal1, velocityBeforeInUnitNormal2);

    Vector2 unitTangent = {unitNormal.y, -unitNormal.x};
    float velocityInUnitTangent1 = Vector2DotProduct(velocityBefore1, unitTangent); // Does not change as no force

    return Vector2Add(Vector2Scale(unitNormal, velocityAfterInUnitNormal1), Vector2Scale(unitTangent, velocityInUnitTangent1));
}

void positionVelocityCorrectionWithBoundingBox(particle* particle1, Rectangle boundingBox) {
    // Bounding Box Detection And Correction 
    if (particle1->position.x + particle1->radius > boundingBox.x + boundingBox.width) {
        // Collision with right side of box
        particle1->position.x = 2.*(boundingBox.x + boundingBox.width - particle1->radius) - particle1->position.x;
        particle1->velocity.x = -particle1->velocity.x;
    }
    if (particle1->position.x - particle1->radius < boundingBox.x) {
        // Collision with left side of box
        particle1->position.x = 2.*(boundingBox.x + particle1->radius) - particle1->position.x;
        particle1->velocity.x = -particle1->velocity.x;
    }
    if (particle1->position.y + particle1->radius > boundingBox.y) {
        // Collision with Top of box
        particle1->position.y = 2.*(boundingBox.y - particle1->radius) - particle1->position.y;
        particle1->velocity.y = -particle1->velocity.y;
    }
    if (particle1->position.y - particle1->radius < boundingBox.y - boundingBox.height) {
        // Collision with Bottom of box
        particle1->position.y = 2.*(boundingBox.y - boundingBox.height + particle1->radius) - particle1->position.y;
        particle1->velocity.y = -particle1->velocity.y;
    }
}

void positionVelocityCorrectionWithTwoParticles(particle* particle1, particle* particle2) {
    const Vector2 positionDifference = Vector2Subtract(particle1->position, particle2->position);
    const Vector2 velocityDifference = Vector2Subtract(particle1->velocity, particle2->velocity);
    const Vector2 velocityDifferencePerp = {velocityDifference.y, -velocityDifference.x};
    const float velocityDifferenceDistanceSquarred = Vector2DotProduct(velocityDifference, velocityDifference);
    const float distanceSquared = (particle1->radius + particle2->radius)*(particle1->radius + particle2->radius);

    float stepBackTime = Vector2DotProduct(positionDifference, velocityDifference);
    stepBackTime += sqrt(distanceSquared*velocityDifferenceDistanceSquarred - Vector2DotProduct(positionDifference, velocityDifferencePerp));;
    stepBackTime /= velocityDifferenceDistanceSquarred;

    particle1->position = Vector2Subtract(particle1->position, Vector2Scale(particle1->velocity, stepBackTime));
    particle2->position = Vector2Subtract(particle2->position, Vector2Scale(particle2->velocity, stepBackTime));
    // Circles are now touching

    

    Vector2 unitNormal = Vector2Subtract(particle1->position, particle2->position);
    unitNormal = Vector2Scale(unitNormal, 1./Vector2Length(unitNormal));
    Vector2 velocityAfter_1 = velocityAfterTwoDimCollision(particle1->mass, particle2->mass, particle1->velocity, particle2->velocity, unitNormal);
    Vector2 velocityAfter_2 = velocityAfterTwoDimCollision(particle2->mass, particle1->mass, particle2->velocity, particle1->velocity, unitNormal);
    particle1->velocity = velocityAfter_1;
    particle2->velocity = velocityAfter_2;

    particle1->position = Vector2Add(particle1->position, Vector2Scale(particle1->velocity, stepBackTime));
    particle2->position = Vector2Add(particle2->position, Vector2Scale(particle2->velocity, stepBackTime));
}