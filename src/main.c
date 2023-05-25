#include "raylib.h"
#include "nextstep.h"
#include "render.h"

enum {
    MAX_NUMBER_OF_PARTICLES = 2000,
    screenWidth = 800,
    screenHeight = 400,
};

// Examples
void example1(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 2;
    window->x = 0.;
    window->y = 10.;
    window->height = 10;
    window->width = 20;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

    particles[0].position.x = 5.;
    particles[0].position.y = 5.;
    particles[0].velocity.x = 5.; 
    particles[0].velocity.y = 4.0;
    particles[0].radius = 1.;
    particles[0].color = MAROON;
    particles[0].mass = 1.;

    particles[1].position.x = 7.;
    particles[1].position.y = 7.;
    particles[1].velocity.x = 5.; 
    particles[1].velocity.y = 8.0;
    particles[1].radius = 0.5;
    particles[1].color = YELLOW;
    particles[1].mass = 0.25;
}

// Examples
void example2(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 2000;
    window->x = 0.;
    window->y = 50.;
    window->height = 50;
    window->width = 100;

    resolution->x = screenWidth;
    resolution->y = screenHeight;


    for (size_t i = 0; i < *numberOfParticles; i++) {
        particles[i].position.x = (float)((2*i+1)%100);
        particles[i].position.y = (float) (2 + (2*i+1)/100);
        particles[i].velocity.x = 3.;
        particles[i].velocity.y = 35.;
        particles[i].radius = 0.5;
        particles[i].color = MAROON;
        particles[i].mass = 1.;
    }
    particles[0].color = WHITE;
    particles[0].velocity.y = -3.;
    particles[0].velocity.x = 3.;
}

void example3(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 4;
    window->x = 0.;
    window->y = 10.;
    window->height = 10;
    window->width = 20;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

       particles[0].position.x = 0.9;
    particles[0].position.y = 5.;
    particles[0].velocity.x = -5.; 
    particles[0].velocity.y = 4.0;
    particles[0].radius = 1.;
    particles[0].color = MAROON;
    particles[0].mass = 1.;

    particles[1].position.x = 19.;
    particles[1].position.y = 5.;
    particles[1].velocity.x = 5.; 
    particles[1].velocity.y = 4.0;
    particles[1].radius = 1.5;
    particles[1].color = WHITE;
    particles[1].mass = 1.;

    particles[2].position.x = 10.;
    particles[2].position.y = 1.;
    particles[2].velocity.x = 5.; 
    particles[2].velocity.y = 4.0;
    particles[2].radius = 1.5;
    particles[2].color = GREEN;
    particles[2].mass = 1.;

    particles[3].position.x = 10.;
    particles[3].position.y = 9.;
    particles[3].velocity.x = 5.; 
    particles[3].velocity.y = -4.0;
    particles[3].radius = 1.5;
    particles[3].color = BLUE;
    particles[3].mass = 1.;

}

void example4(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 2;
    window->x = 0.;
    window->y = 10.;
    window->height = 10;
    window->width = 20;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

    particles[0].position.x = 1.5;
    particles[0].position.y = 5.;
    particles[0].velocity.x = 0.; 
    particles[0].velocity.y = -4.0;
    particles[0].radius = 1.;
    particles[0].color = MAROON;
    particles[0].mass = 1.;

    particles[1].position.x = 2.5;
    particles[1].position.y = 5.;
    particles[1].velocity.x = 0.; 
    particles[1].velocity.y = 4.0;
    particles[1].radius = 1.;
    particles[1].color = WHITE;
    particles[1].mass = 1.;


}
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
    const float deltaTime = 1/240.;

    Rectangle window;
    Vector2 resolution;
    size_t numberOfParticles;
    particle particles[MAX_NUMBER_OF_PARTICLES];

    example2(&window, &resolution, &numberOfParticles, particles);


    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        nextStep(particles, numberOfParticles, deltaTime, window);
        nextStep(particles, numberOfParticles, deltaTime, window);
        nextStep(particles, numberOfParticles, deltaTime, window);
        nextStep(particles, numberOfParticles, deltaTime, window);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        displayParticle(particles, numberOfParticles, window, resolution);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}