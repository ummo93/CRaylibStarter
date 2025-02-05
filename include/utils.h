#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"
#include "raymath.h"

Vector2 GetHeadingByRotation2D(float rotation, Vector2 absoluteHeading)
{
    absoluteHeading = Vector2Rotate(absoluteHeading, rotation * DEG2RAD);
    absoluteHeading = Vector2Normalize(absoluteHeading);
    return absoluteHeading;
}

Vector2 GetForwardVector2D(float rotation)
{
    return GetHeadingByRotation2D(rotation, (Vector2) { 0.0f, -1.0f }); // by up vector
}

Vector2 GetRightVector2D(float rotation)
{
    return GetHeadingByRotation2D(rotation, (Vector2) { 1.0f, 0.0f }); // by right vector
}

Vector2 Translate2D(Vector2 origin, Vector2 dir, float strength)
{
    return Vector2Add(origin, Vector2Scale(dir, strength));
}

#endif