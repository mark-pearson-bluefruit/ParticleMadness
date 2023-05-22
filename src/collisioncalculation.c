#include "collisioncalculation.h"

float velocityAfterOneDimCollision(float mass1, float mass2, float velocityBefore1, float velocityBefore2) {
    return ((mass1 - mass2)*velocityBefore1 + 2.*mass2*velocityBefore2)/(mass1 + mass2);
}

Vector2 velocityAfterTwoDimCollision(float mass1, float mass2, Vector2 velocityBefore1, Vector2 velocityBefore2, Vector2 unitNormal) {
    return {velocityAfterOneDimCollision(mass1, mass2, velocityBefore1.x, velocityBefore2.x), 0.0f};
}