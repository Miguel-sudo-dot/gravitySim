#include "raylib.h"

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
    Object object = InitialiseObject(400, 0, 0, 23, WHITE);
    float acceleration = 0.25;

    InitWindow(screenWidth, screenHeight, "Gravity");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        object.velocity += acceleration;
        object.y += object.velocity;

        if(object.y+object.radius >= screenHeight){
            object.y = screenHeight-object.radius;
            object.velocity*=-1;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawCircle(object.x, object.y, object.radius, object.color);

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