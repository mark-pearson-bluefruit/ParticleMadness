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
        particles[i].radius = 0.4;
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

void example5(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 3;
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
    particles[1].velocity.y = 0.;
    particles[1].radius = 1.;
    particles[1].color = WHITE;
    particles[1].mass = 1.;

    particles[2].position.x = 3.8;
    particles[2].position.y = 5.;
    particles[2].velocity.x = 0.; 
    particles[2].velocity.y = 4.;
    particles[2].radius = 1.;
    particles[2].color = GREEN;
    particles[2].mass = 1.;


}

void exampleSnooker(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 16;
    window->x = 0.;
    window->y = 50.;
    window->height = 50;
    window->width = 100;

    const float ballRadius = 1.;
    const float yStep = ballRadius;
    const float xStep = sqrt(3)*ballRadius;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

    particles[0].position.x = 15.;
    particles[0].position.y = 25.;
    particles[0].velocity.x = 35.0; 
    particles[0].velocity.y = 0.;
    particles[0].radius = ballRadius;
    particles[0].color = WHITE;
    particles[0].mass = 1.;

    particles[1].position.x = 65.;
    particles[1].position.y = 25.;
    particles[1].velocity.x = 0.; 
    particles[1].velocity.y = 0.0;
    particles[1].radius = ballRadius;
    particles[1].color = YELLOW;
    particles[1].mass = 1.;


    particles[2].position.x = 65. + xStep;
    particles[2].position.y = 25. + yStep;
    particles[2].velocity.x = 0.; 
    particles[2].velocity.y = 0.0;
    particles[2].radius = ballRadius;
    particles[2].color = YELLOW;
    particles[2].mass = 1.;

    particles[3].position.x = 65. + xStep;
    particles[3].position.y = 25. - yStep;
    particles[3].velocity.x = 0.; 
    particles[3].velocity.y = 0.0;
    particles[3].radius = ballRadius;
    particles[3].color = RED;
    particles[3].mass = 1.;

    particles[4].position.x = 65. + 2.*xStep;
    particles[4].position.y = 25. + 2.*yStep;
    particles[4].velocity.x = 0.; 
    particles[4].velocity.y = 0.0;
    particles[4].radius = ballRadius;
    particles[4].color = RED;
    particles[4].mass = 1.;

    particles[5].position.x = 65. + 2.*xStep;
    particles[5].position.y = 25.;
    particles[5].velocity.x = 0.; 
    particles[5].velocity.y = 0.0;
    particles[5].radius = ballRadius;
    particles[5].color = GREEN;
    particles[5].mass = 1.;

    particles[6].position.x = 65. + 2.*xStep;
    particles[6].position.y = 25. - 2.*yStep;
    particles[6].velocity.x = 0.; 
    particles[6].velocity.y = 0.0;
    particles[6].radius = ballRadius;
    particles[6].color = YELLOW;
    particles[6].mass = 1.;

    particles[7].position.x = 65. + 3.*xStep;
    particles[7].position.y = 25. + 3.*yStep;
    particles[7].velocity.x = 0.; 
    particles[7].velocity.y = 0.0;
    particles[7].radius = ballRadius;
    particles[7].color = YELLOW;
    particles[7].mass = 1.;

    particles[8].position.x = 65. + 3.*xStep;
    particles[8].position.y = 25. + 1.*yStep;
    particles[8].velocity.x = 0.; 
    particles[8].velocity.y = 0.0;
    particles[8].radius = ballRadius;
    particles[8].color = RED;
    particles[8].mass = 1.;

    particles[9].position.x = 65. + 3.*xStep;
    particles[9].position.y = 25. - 1.*yStep;
    particles[9].velocity.x = 0.; 
    particles[9].velocity.y = 0.0;
    particles[9].radius = ballRadius;
    particles[9].color = YELLOW;
    particles[9].mass = 1.;

    particles[10].position.x = 65. + 3.*xStep;
    particles[10].position.y = 25. - 3.*yStep;
    particles[10].velocity.x = 0.; 
    particles[10].velocity.y = 0.0;
    particles[10].radius = ballRadius;
    particles[10].color = RED;
    particles[10].mass = 1.;

    particles[11].position.x = 65. + 4.*xStep;
    particles[11].position.y = 25. + 4.*yStep;
    particles[11].velocity.x = 0.; 
    particles[11].velocity.y = 0.0;
    particles[11].radius = ballRadius;
    particles[11].color = RED;
    particles[11].mass = 1.;

    particles[12].position.x = 65. + 4.*xStep;
    particles[12].position.y = 25. + 2.*yStep;
    particles[12].velocity.x = 0.; 
    particles[12].velocity.y = 0.0;
    particles[12].radius = ballRadius;
    particles[12].color = YELLOW;
    particles[12].mass = 1.;

    
    particles[13].position.x = 65. + 4.*xStep;
    particles[13].position.y = 25.;
    particles[13].velocity.x = 0.; 
    particles[13].velocity.y = 0.0;
    particles[13].radius = ballRadius;
    particles[13].color = RED;
    particles[13].mass = 1.;

    particles[14].position.x = 65. + 4.*xStep;
    particles[14].position.y = 25. - 2.*yStep;
    particles[14].velocity.x = 0.; 
    particles[14].velocity.y = 0.0;
    particles[14].radius = ballRadius;
    particles[14].color = RED;
    particles[14].mass = 1.;

    particles[15].position.x = 65. + 4.*xStep;
    particles[15].position.y = 25. - 4.*yStep;
    particles[15].velocity.x = 0.; 
    particles[15].velocity.y = 0.0;
    particles[15].radius = ballRadius;
    particles[15].color = YELLOW;
    particles[15].mass = 1.;
}

void exampleNewtonsCradel(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 5;
    window->x = 0.;
    window->y = 20.;
    window->height = 20;
    window->width = 40;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

    const float xStep = 2.*1.;

    particles[0].position.x = 2.;
    particles[0].position.y = 10.;
    particles[0].velocity.x = 15.; 
    particles[0].velocity.y = 0.;
    particles[0].radius = 1.;
    particles[0].color = MAROON;
    particles[0].mass = 1.;

    for (size_t i = 0; i < *numberOfParticles; i++) {
        particles[i+1].position.x = 17. + i*xStep;
        particles[i+1].position.y = 10.;
        particles[i+1].velocity.x = 0.; 
        particles[i+1].velocity.y = 0.0;
        particles[i+1].radius = 1.;
        particles[i+1].color = WHITE;
        particles[i+1].mass = 1.;
    }
}

void exampleBigBallLittleBall(Rectangle* window, Vector2* resolution, size_t* numberOfParticles, particle* particles) {
    *numberOfParticles = 2;
    window->x = 0.;
    window->y = 20.;
    window->height = 20;
    window->width = 40;

    resolution->x = screenWidth;
    resolution->y = screenHeight;

    particles[0].position.x = 2.;
    particles[0].position.y = 10.;
    particles[0].velocity.x = 0.; 
    particles[0].velocity.y = 0.;
    particles[0].radius = 1.;
    particles[0].color = MAROON;
    particles[0].mass = 1.;

    particles[1].position.x = 30.;
    particles[1].position.y = 10.;
    particles[1].velocity.x = -10.; 
    particles[1].velocity.y = 0.0;
    particles[1].radius = 9.;
    particles[1].color = WHITE;
    particles[1].mass = 81.;

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