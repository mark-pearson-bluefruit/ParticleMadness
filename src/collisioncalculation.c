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