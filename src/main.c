#include "raylib.h"
#include "math.h"

#define NUMBER_OBJECTS 2
#define G 398600 // km^3 / (masas terrestre * s^2)
#define SCALE_FACTOR 100 // 1px -> 100km

typedef struct{
    float x, y;
    Vector2 velocity;
    float radius;
    Color color;
    float mass; // en masas terrestres
}Object;

Object InitialiseObject(float x, float y, Vector2 velocity, float radius, Color color, float mass){
    Object object;
    object.x = x;
    object.y = y;
    object.velocity = velocity;
    object.radius = radius;
    object.color = color;
    object.mass = mass;
    return object;
}

int main(void){
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 800;
    Object object[NUMBER_OBJECTS];
    object[0] = InitialiseObject(400, 0, (Vector2){200,0}, 10, GRAY, 1*1000); 
    object[1] = InitialiseObject(400, 400, (Vector2){0,0}, 30, RED, 10*1000); 

    InitWindow(screenWidth, screenHeight, "Gravity");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        float dt = GetFrameTime()*50;
        for(int i=0; i<NUMBER_OBJECTS; i++){
            for(int j=0; j<NUMBER_OBJECTS; j++){
                if(j!=i){
                    float dx = (object[j].x-object[i].x)*SCALE_FACTOR;
                    float dy = (object[j].y-object[i].y)*SCALE_FACTOR;
                    float module = sqrt(dx*dx + dy*dy);
                    float force = ((G*object[i].mass*object[j].mass)/(module*module));
                    float acceleration = force/object[i].mass;
                    Vector2 vu = {dx/module, dy/module};
                    object[i].velocity.x += acceleration*vu.x*dt;
                    object[i].velocity.y += acceleration*vu.y*dt;
                }
            }
            object[i].x += object[i].velocity.x*dt/SCALE_FACTOR;
            object[i].y += object[i].velocity.y*dt/SCALE_FACTOR;
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