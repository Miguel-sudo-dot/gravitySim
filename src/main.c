#include "raylib.h"
#include "math.h"
#include "stdio.h"

#define NUMBER_OBJECTS 3
#define G 398600 // km^3 / (masas terrestre * s^2)
#define SCALE_FACTOR 100 // 1px -> 100km

typedef struct{
    float x, y;
    Vector2 velocity;
    float radius;
    Color color;
    float mass; // en masas terrestres
}Object;

typedef struct{
    Vector2 initialPos;
    Vector2 finalPos;
    int drawingArrow;
    int draw;
}Arrow;


void DrawArrow(Arrow *arrow){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && arrow->drawingArrow==0){
        arrow->initialPos = GetMousePosition();
        arrow->drawingArrow = 1;
        arrow->draw = 0;
        printf("\nPRESIONADO");
    }
    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT) && arrow->drawingArrow==1){
        arrow->finalPos = GetMousePosition();
        arrow->drawingArrow = 0;
        arrow->draw = 1;
        printf("\nSOLTADO");
    }
}

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
    Arrow arrow;
    arrow.drawingArrow = 0;
    object[0] = InitialiseObject(100, 100, (Vector2){200, -50}, 10, GRAY, 200); 
    object[1] = InitialiseObject(400, 400, (Vector2){0,0}, 30, RED, 10*1000); 
    object[2]= InitialiseObject(600, 500, (Vector2){-265, 150}, 5, YELLOW, 150);

    InitWindow(screenWidth, screenHeight, "Gravity");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        float dt = GetFrameTime()*30;
        for(int i=0; i<NUMBER_OBJECTS; i++){
            for(int j=0; j<NUMBER_OBJECTS; j++){
                if(j!=i){
                    float dx = (object[j].x-object[i].x)*SCALE_FACTOR;
                    float dy = (object[j].y-object[i].y)*SCALE_FACTOR;
                    float module = sqrt(dx*dx + dy*dy);
                    if(module<=5) module=5;
                    float force = ((G*object[i].mass*object[j].mass)/(module*module));
                    float acceleration = force/object[i].mass;
                    Vector2 vu = {dx/module, dy/module};
                    object[i].velocity.x += acceleration*vu.x*dt;
                    object[i].velocity.y += acceleration*vu.y*dt;
                }
            }
            
        }
        for(int i=0; i<NUMBER_OBJECTS; i++){
            object[i].x += object[i].velocity.x*dt/SCALE_FACTOR;
            object[i].y += object[i].velocity.y*dt/SCALE_FACTOR;
        }
        DrawArrow(&arrow);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            for(int i=0; i<NUMBER_OBJECTS; i++){
                DrawCircle(object[i].x, object[i].y, object[i].radius, object[i].color);
            }
            if(arrow.drawingArrow==1){
                DrawLineEx(arrow.initialPos, GetMousePosition(), 2, RAYWHITE);
                float dx = GetMousePosition().x-arrow.initialPos.x;
                float dy = GetMousePosition().y-arrow.initialPos.y;
                float module = sqrt(dx*dx+dy*dy);
                Vector2 vu = {dx/module, dy/module};
                vu = (Vector2){vu.x*10,vu.y*10};
                Vector2 vn1 = {-vu.y, vu.x};
                Vector2 vn2 = {vu.y, -vu.x};
                DrawTriangle(
                    GetMousePosition(), 
                    (Vector2){-vu.x+vn2.x+GetMousePosition().x, -vu.y+vn2.y+GetMousePosition().y},
                    (Vector2){-vu.x+vn1.x+GetMousePosition().x, -vu.y+vn1.y+GetMousePosition().y},
                    RAYWHITE
                );
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