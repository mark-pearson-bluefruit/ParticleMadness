#ifndef COLLISIONCALCULATION_H
#define COLLISIONCALCULATION_H

#include "Raylib.h"

float velocityAfterOneDimCollision(float mass1, float mass2, float velocityBefore1, float velocityBefore2); // PRIVATE FUNCTION
Vector2 velocityAfterTwoDimCollision(float mass1, float mass2, Vector2 velocityBefore1, Vector2 velocityBefore2, Vector2 unitNormal);

#endif // COLLISIONCALCULATION_H