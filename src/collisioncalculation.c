#include "collisioncalculation.h"

float velocityAfterOneDimCollision(float mass1, float mass2, float velocityBefore1, float velocityBefore2) {
    return ((mass1 - mass2)*velocityBefore1 + 2.*mass2*velocityBefore2)/(mass1 + mass2);
}