#include "include/fff.h"
#include "gtest/gtest.h"

#include <cmath>

#include "raylib.h"
#include "render.h"
#include "particle.h"
#include "nextstep.h"
#include "collisioncalculation.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(DrawCircle, int, int, float, Color);

bool colorsEqual(Color colorOne, Color colorTwo) {
    if (colorOne.r != colorTwo.r)
        return false;
    if (colorOne.g != colorTwo.g)
        return false;
    if (colorOne.b != colorTwo.b)
        return false;
    if (colorOne.a != colorTwo.a)
        return false;
    return true;
}

class Display : public testing::Test
{
public:
    void SetUp()
    {
        RESET_FAKE(DrawCircle);
        FFF_RESET_HISTORY();
    }
};

TEST_F(Display, DisplayAllCirclesFromParticleDataCorrectly) {
    // Given 
    
    const size_t number_of_particles = 3;
    const float windowX = 0.;
    const float windowY = 1.5; // Top left position of viewing window
    const float windowWidth = 2.;
    const float windowHeight = 1.5;
    const int resolutionX = 800;
    const int resolutionY = 600;
    Rectangle window = {windowX, windowY, windowWidth, windowHeight};
    Vector2 resolution = {resolutionX, resolutionY};

    particle particles[number_of_particles];
    particles[0].position = {0., 0.};
    particles[1].position = {1., 0.75};
    particles[2].position = {1.75, 1.4};

    particles[0].radius = 0.9;
    particles[1].radius = 0.05;
    particles[2].radius = 0.1;

    particles[0].color = MAROON;
    particles[1].color = RED;
    particles[2].color = BLACK;
    
    // When
    displayParticle(particles, number_of_particles, window, resolution);

    // Then
    ASSERT_EQ(3, DrawCircle_fake.call_count);

    // 1st Call
    ASSERT_EQ(0, DrawCircle_fake.arg0_history[0]);
    ASSERT_EQ(resolutionY - 0 - 1, DrawCircle_fake.arg1_history[0]);
    ASSERT_EQ(360., DrawCircle_fake.arg2_history[0]);
    ASSERT_TRUE(colorsEqual(MAROON, DrawCircle_fake.arg3_history[0]));

    // 2nd Call
    ASSERT_EQ(400, DrawCircle_fake.arg0_history[1]);
    ASSERT_EQ(resolutionY - 300 - 1, DrawCircle_fake.arg1_history[1]);
    ASSERT_EQ(20., DrawCircle_fake.arg2_history[1]);
    ASSERT_TRUE(colorsEqual(RED, DrawCircle_fake.arg3_history[1]));

    // 3rd Call
    ASSERT_EQ(700, DrawCircle_fake.arg0_history[2]);
    ASSERT_EQ(resolutionY - 560 - 1, DrawCircle_fake.arg1_history[2]);
    ASSERT_EQ(40., DrawCircle_fake.arg2_history[2]);
    ASSERT_TRUE(colorsEqual(BLACK, DrawCircle_fake.arg3_history[2]));
}

TEST_F(Display, DisplayParticleDataWhenWindowNotAtOriginCorrectly) {
    // Given     
    const size_t number_of_particles = 1;
    const float windowX = 5.;
    const float windowY = 6.; // Top left position of viewing window
    const float windowWidth = 4.;
    const float windowHeight = 2.;
    const int resolutionX = 800;
    const int resolutionY = 400;
    Rectangle window = {windowX, windowY, windowWidth, windowHeight};
    Vector2 resolution = {resolutionX, resolutionY};

    particle particles[number_of_particles];
    particles[0].position = {7., 5.5};
    particles[0].radius = 0.5;
    particles[0].color = MAROON;
    
    // When
    displayParticle(particles, number_of_particles, window, resolution);

    // Then
    ASSERT_EQ(1, DrawCircle_fake.call_count);

    // 1st Call
    ASSERT_EQ(400, DrawCircle_fake.arg0_history[0]);
    ASSERT_EQ(resolutionY - 300 - 1, DrawCircle_fake.arg1_history[0]);
    ASSERT_EQ(100., DrawCircle_fake.arg2_history[0]);
    ASSERT_TRUE(colorsEqual(MAROON, DrawCircle_fake.arg3_history[0]));
}

class Calculation : public testing::Test
{
public:
    void SetUp()
    {

    }
};

TEST_F(Calculation, TheNextTimeStepIsCalculatedCorrectly) {
    // Given
    const size_t number_of_particles = 2;
    const float deltaTime = 0.1;
    Rectangle box;
    box.height =  20.;
    box.width = 40.;
    box.x = 0.;
    box.y = 20.;

    particle particles[number_of_particles];
    particles[0].position = {7., 5.5};
    particles[1].position = {3., 6.5};

    particles[0].radius = 1.;
    particles[1].radius = 1.;

    particles[0].velocity = {1., 2.1};
    particles[1].velocity = {-1., -3.};

    // When
    nextStep(particles, number_of_particles, deltaTime, box);

    // Then
    ASSERT_EQ(7.1f, particles[0].position.x);
    ASSERT_EQ(5.71f, particles[0].position.y);
    ASSERT_EQ(2.9f, particles[1].position.x);
    ASSERT_EQ(6.2f, particles[1].position.y);
}

TEST_F(Calculation, NextTimeStepDetectsBoundaryCollisions) {
    // Given
    const size_t number_of_particles = 4;
    const float deltaTime = 0.1;
    Rectangle box;
    box.height =  10.;
    box.width = 40.;
    box.x = 1.;
    box.y = 20.;

    particle particles[number_of_particles];
    particles[0].position = {2., 15.};
    particles[1].position = {40., 15.};
    particles[2].position = {20., 19.};
    particles[3].position = {20., 11.};

    particles[0].radius = 1.1;
    particles[1].radius = 1.4;
    particles[2].radius = 1.2;
    particles[3].radius = 1.3;

    particles[0].velocity = {-1., -0.1};
    particles[1].velocity = {2., 0.1};
    particles[2].velocity = {0.1, 1.};
    particles[3].velocity = {-0.1, -2.};

    // When
    nextStep(particles, number_of_particles, deltaTime, box);

    // Then

    // Position Check

    ASSERT_FLOAT_EQ(2.3f, particles[0].position.x);
    ASSERT_FLOAT_EQ(14.99f, particles[0].position.y); //
    ASSERT_FLOAT_EQ(39.0f, particles[1].position.x);
    ASSERT_FLOAT_EQ(15.01f, particles[1].position.y); //
    ASSERT_FLOAT_EQ(20.01f, particles[2].position.x); //
    ASSERT_FLOAT_EQ(18.5f, particles[2].position.y);
    ASSERT_FLOAT_EQ(19.99f, particles[3].position.x); //
    ASSERT_FLOAT_EQ(11.8f, particles[3].position.y);

    // Velocity Check
    ASSERT_EQ(1.f, particles[0].velocity.x);
    ASSERT_EQ(-0.1f, particles[0].velocity.y);
    ASSERT_EQ(-2.f, particles[1].velocity.x);
    ASSERT_EQ(0.1f, particles[1].velocity.y);
    ASSERT_EQ(0.1f, particles[2].velocity.x);
    ASSERT_EQ(-1.f, particles[2].velocity.y);
    ASSERT_EQ(-0.1f, particles[3].velocity.x);
    ASSERT_EQ(2.f, particles[3].velocity.y);   
}

TEST_F(Calculation, NextTimeStepDetectsParticleCollisions) {
    // Given
    const size_t number_of_particles = 2;
    const float deltaTime = 0.1;
    Rectangle box;
    box.height =  10.;
    box.width = 10.;
    box.x = 0.;
    box.y = 10.;

    particle particles[number_of_particles];
    particles[0].position = {4., 6.};
    particles[1].position = {6., 4.};

    particles[0].radius = 2.0;
    particles[1].radius = 1.0;

    particles[0].velocity = {5.5, 1.0};
    particles[1].velocity = {-0.5, -1.0};

    particles[0].mass = 4.0;
    particles[1].mass = 8.0;

    // When
    nextStep(particles, number_of_particles, deltaTime, box);

    // Then
    Vector2 expectedVelocity[number_of_particles];
    expectedVelocity[0] = {17.0/6.0, 22.0/6.0};
    expectedVelocity[1] = {5.0/6.0, -7.0/3.0};

    // Velocity Check
    ASSERT_FLOAT_EQ(expectedVelocity[0].x, particles[0].velocity.x);
    ASSERT_FLOAT_EQ(expectedVelocity[0].y, particles[0].velocity.y);
    ASSERT_FLOAT_EQ(expectedVelocity[1].x, particles[1].velocity.x);
    ASSERT_FLOAT_EQ(expectedVelocity[1].y, particles[1].velocity.y);

    // Position Check   
    ASSERT_FLOAT_EQ(4. + expectedVelocity[0].x*deltaTime, particles[0].position.x);
    ASSERT_FLOAT_EQ(6. + expectedVelocity[0].y*deltaTime, particles[0].position.y);
    ASSERT_FLOAT_EQ(6. + expectedVelocity[1].x*deltaTime, particles[1].position.x);
    ASSERT_FLOAT_EQ(4. + expectedVelocity[1].y*deltaTime, particles[1].position.y);    
}

TEST(CollisionCalculation, CalculateContinuousCollisionBetweenParticleAndBoxCorrectly) {
    // Given
    const size_t number_of_particles = 4;
    Rectangle box;
    box.height =  10.;
    box.width = 20.;
    box.x = 0.;
    box.y = 10.;

    particle particles[number_of_particles];
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
    particles[2].velocity.y = -4.0;
    particles[2].radius = 1.5;
    particles[2].color = GREEN;
    particles[2].mass = 1.;

    particles[3].position.x = 10.;
    particles[3].position.y = 9.;
    particles[3].velocity.x = 5.; 
    particles[3].velocity.y = 4.0;
    particles[3].radius = 1.5;
    particles[3].color = BLUE;
    particles[3].mass = 1.;

    // When
    positionVelocityCorrectionWithBoundingBox(&particles[0], box);
    positionVelocityCorrectionWithBoundingBox(&particles[1], box);
    positionVelocityCorrectionWithBoundingBox(&particles[2], box);
    positionVelocityCorrectionWithBoundingBox(&particles[3], box);

    // Then
    // Position Check
    
    ASSERT_FLOAT_EQ(1.1f, particles[0].position.x);
    ASSERT_FLOAT_EQ(5.f, particles[0].position.y);
    ASSERT_FLOAT_EQ(18.f, particles[1].position.x);
    ASSERT_FLOAT_EQ(5.f, particles[1].position.y);    
    ASSERT_FLOAT_EQ(10.f, particles[2].position.x);
    ASSERT_FLOAT_EQ(2.0f, particles[2].position.y);
    ASSERT_FLOAT_EQ(10.f, particles[3].position.x);
    ASSERT_FLOAT_EQ(8.f, particles[3].position.y);
    

    // Velocity Check
    ASSERT_FLOAT_EQ(5.f, particles[0].velocity.x);
    ASSERT_FLOAT_EQ(4.f, particles[0].velocity.y);
    ASSERT_FLOAT_EQ(-5.f, particles[1].velocity.x);
    ASSERT_FLOAT_EQ(4.f, particles[1].velocity.y);
    ASSERT_FLOAT_EQ(5.f, particles[2].velocity.x);
    ASSERT_FLOAT_EQ(4.f, particles[2].velocity.y);
    ASSERT_FLOAT_EQ(5.f, particles[3].velocity.x);
    ASSERT_FLOAT_EQ(-4.f, particles[3].velocity.y);   

}

TEST(CollisionCalculation, CalculateBasicCorrectionOfOverlapBetweenTwoParticlesCorrectly) {
    // Given
    const size_t number_of_particles = 2;
    Rectangle box;
    box.height =  20.;
    box.width = 25.;
    box.x = 0.;
    box.y = 20.;

    particle particles[number_of_particles];

    particles[0].position.x = 4.;
    particles[0].position.y = 4.;
    particles[0].radius = 1.;
    particles[0].mass = 3.;

    particles[1].position.x = 5.;
    particles[1].position.y = 4.;
    particles[1].radius = 1.;
    particles[1].mass = 1.;



    // When
    positionVelocityOverlapCorrectionWithTwoParticles(&particles[0], &particles[1]);

    // Then

    ASSERT_FLOAT_EQ(3.75, particles[0].position.x);
    ASSERT_FLOAT_EQ(4., particles[0].position.y);
    ASSERT_FLOAT_EQ(5.75, particles[1].position.x);
    ASSERT_FLOAT_EQ(4., particles[1].position.y);

}

TEST(CollisionCalculation, CalculateContinuousCollisionBetweenTwoParticlesCorrectly) {
    // Given
    const size_t number_of_particles = 4;
    Rectangle box;
    box.height =  20.;
    box.width = 25.;
    box.x = 0.;
    box.y = 20.;

    particle particles[number_of_particles];

    // Collision 1 
    particles[0].position.x = 4.;
    particles[0].position.y = 10.;
    particles[0].velocity.x = 5.; 
    particles[0].velocity.y = 0.0;
    particles[0].radius = 1.;
    particles[0].mass = 5.;

    particles[1].position.x = 5.5;
    particles[1].position.y = 10.;
    particles[1].velocity.x = -10.; 
    particles[1].velocity.y = 0.0;
    particles[1].radius = 1.;
    particles[1].mass = 5.;


    // Collision 2
    particles[2].position.x = 14.;
    particles[2].position.y = 10.;
    particles[2].velocity.x = 2.; 
    particles[2].velocity.y = 2.;
    particles[2].radius = 1.5;
    particles[2].mass = 5.;


    particles[3].position.x = 16.;
    particles[3].position.y = 12.;
    particles[3].velocity.x = -1.; 
    particles[3].velocity.y = -1.;
    particles[3].radius = 2.;
    particles[3].mass = 5.;

    // When
    positionVelocityCorrectionWithTwoParticles(&particles[0], &particles[1]);
    positionVelocityCorrectionWithTwoParticles(&particles[2], &particles[3]);

    // Then

    // Collision 1
    ASSERT_FLOAT_EQ(3.5, particles[0].position.x);
    ASSERT_FLOAT_EQ(10., particles[0].position.y);
    ASSERT_FLOAT_EQ(6., particles[1].position.x);
    ASSERT_FLOAT_EQ(10., particles[1].position.y);

    ASSERT_FLOAT_EQ(-10., particles[0].velocity.x);
    ASSERT_FLOAT_EQ(0., particles[0].velocity.y);
    ASSERT_FLOAT_EQ(5., particles[1].velocity.x);
    ASSERT_FLOAT_EQ(0., particles[1].velocity.y);

    // Collision 2
    ASSERT_FLOAT_EQ((64.-7.*sqrt(2))/4., particles[2].position.x);
    ASSERT_FLOAT_EQ((48.-7.*sqrt(2))/4., particles[2].position.y);
    ASSERT_FLOAT_EQ(16.47487373, particles[3].position.x);
    ASSERT_FLOAT_EQ(12.47487373, particles[3].position.y);

    ASSERT_FLOAT_EQ(-1., particles[2].velocity.x);
    ASSERT_FLOAT_EQ(-1., particles[2].velocity.y);
    ASSERT_FLOAT_EQ(2., particles[3].velocity.x);
    ASSERT_FLOAT_EQ(2., particles[3].velocity.y);



}

TEST(CollisionCalculation, CalculateOneDimCollisionsCorrectly) {
    // Given
    float mass1 = 1.0;
    float mass2 = 1.0;
    float velocityBefore1 = 5.5;
    float velocityBefore2 = 2.1;

    // When
    float velocityAfter1 = velocityAfterOneDimCollision(mass1, mass2, velocityBefore1, velocityBefore2);
    float velocityAfter2 = velocityAfterOneDimCollision(mass2, mass1, velocityBefore2, velocityBefore1);

    // Then
    ASSERT_EQ(2.1f, velocityAfter1);
    ASSERT_EQ(5.5f, velocityAfter2);

    // Given
    mass1 = 5.5;
    mass2 = 0.5;
    velocityBefore1 = 1.0;
    velocityBefore2 = 100.0;

    // When
    velocityAfter1 = velocityAfterOneDimCollision(mass1, mass2, velocityBefore1, velocityBefore2);
    velocityAfter2 = velocityAfterOneDimCollision(mass2, mass1, velocityBefore2, velocityBefore1);

    // Then
    ASSERT_EQ(17.5f, velocityAfter1);
    ASSERT_EQ(-81.5f, velocityAfter2);
}

TEST(CollisionCalculation, CalculateTwoDimCollisionsCorrectly) {
    // Given
    float mass1 = 4.0;
    float mass2 = 8.0;
    Vector2 velocityBefore1 = {5.5, 0.0};
    Vector2 velocityBefore2 = {-0.5, 0.0};
    Vector2 unitNormal = {1., 0.};

    // When
    Vector2 velocityAfter1 = velocityAfterTwoDimCollision(mass1, mass2, velocityBefore1, velocityBefore2, unitNormal);
    Vector2 velocityAfter2 = velocityAfterTwoDimCollision(mass2, mass1, velocityBefore2, velocityBefore1, unitNormal);

    // Then
    ASSERT_EQ(-2.5f, velocityAfter1.x);
    ASSERT_EQ(0.f, velocityAfter1.y);
    ASSERT_EQ(3.5f, velocityAfter2.x);
    ASSERT_EQ(0.f, velocityAfter2.y);

    // Given
    mass1 = 4.0;
    mass2 = 8.0;
    velocityBefore1 = {5.5, 1.0};
    velocityBefore2 = {-0.5, -1.0};
    unitNormal = {1./sqrt(2), -1./sqrt(2)};

    // When
    velocityAfter1 = velocityAfterTwoDimCollision(mass1, mass2, velocityBefore1, velocityBefore2, unitNormal);
    velocityAfter2 = velocityAfterTwoDimCollision(mass2, mass1, velocityBefore2, velocityBefore1, unitNormal);

    // Then
    ASSERT_FLOAT_EQ(17.0/6.0, velocityAfter1.x);
    ASSERT_FLOAT_EQ(44.0f/12.0f, velocityAfter1.y);
    ASSERT_FLOAT_EQ(5.0f/6.0f, velocityAfter2.x);
    ASSERT_FLOAT_EQ(-7.0f/3.0f, velocityAfter2.y);
}

TEST(CollisionCalculation, DetectACollisionBetweenTwoCircles) {
    // Given
    particle particle1;
    particle1.position = {1., 2.};
    particle1.radius = 2;
    particle particle2;
    particle2.position = {0.5, 1.5};
    particle2.radius = 1;
    particle particle3;
    particle3.position = {5, 6};
    particle3.radius = 1;

    // Then
    ASSERT_TRUE(doParticlesOverlap(particle1, particle2));
    ASSERT_FALSE(doParticlesOverlap(particle2, particle3));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}