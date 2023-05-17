#include "raylib.h"
#include "nextstep.h"
#include "render.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    const float deltaTime = 1./60.;
    const size_t numberOfParticles = 2;
    particle particles[numberOfParticles];
    Rectangle window;
    window.x = 0.;
    window.y = 10.;
    window.height = 10;
    window.width = 20;

    Vector2 resolution = {screenWidth, screenHeight};

    particles[0].position.x = 5.;
    particles[0].position.y = 5.;
    particles[0].velocity.x = 65.; 
    particles[0].velocity.y = 80.0;
    particles[0].radius = 1.;
    particles[0].color = MAROON;

    particles[1].position.x = 7.;
    particles[1].position.y = 7.;
    particles[1].velocity.x = 5.; 
    particles[1].velocity.y = 8.0;
    particles[1].radius = 0.5;
    particles[1].color = YELLOW;

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        nextStep(particles, numberOfParticles, deltaTime, window);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        displayParticle(particles, numberOfParticles, window, resolution);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}