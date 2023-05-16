#include "include/fff.h"
#include "gtest/gtest.h"

#include "raylib.h"
#include "render.h"
#include "particle.h"

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

TEST(MyTestCase, TestOne) {
    int x = 1;
    EXPECT_EQ(x, 1);
}

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}