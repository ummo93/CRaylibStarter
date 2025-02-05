#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"

struct {
    Camera2D* camera;
} typedef Context;

struct {
    int id;
    bool instantiated;
    Vector2 position;
    Vector2 rotation;
    Texture2D texture;
} typedef Actor;

#endif