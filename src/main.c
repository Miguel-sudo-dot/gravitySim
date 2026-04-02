#include "raylib.h"

#define NUMBER_OBJECTS 2

typedef struct{
    float x, y;
    float velocity;
    float radius;
    Color color;
    //float mass;
}Object;

Object InitialiseObject(float x, float y, float velocity, float radius, Color color){
    Object object;
    object.x = x;
    object.y = y;
    object.velocity = velocity;
    object.radius = radius;
    object.color = color;
    return object;
}

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 800;
    Object object[NUMBER_OBJECTS];
    object[0] = InitialiseObject(400, 0, 0, 23, WHITE);
    object[1] = InitialiseObject(250, 0, 10, 10, WHITE);
    float acceleration = 0.25;

    InitWindow(screenWidth, screenHeight, "Gravity");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        for(int i=0; i<NUMBER_OBJECTS; i++){
            object[i].velocity += acceleration;
            object[i].y += object[i].velocity;
            if(object[i].y+object[i].radius >= screenHeight){
                object[i].y = screenHeight-object[i].radius;
                object[i].velocity*=-1;
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            for(int i=0; i<NUMBER_OBJECTS; i++){
                DrawCircle(object[i].x, object[i].y, object[i].radius, object[i].color);
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

/*
gcc src/main.c -o app.exe -Iraylib/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
*/