#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

typedef struct {
    float x, y;
    float radius;
    Vector3 initial_speed; //El tercer elemento es el angulo
    float mass;
    //Rectangle hitbox;
    Vector4 color;
} Object;

void Initialize_object(Object *a);
void Update_Object(Object *a);

#endif