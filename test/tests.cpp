#include "include/fff.h"
#include "gtest/gtest.h"
#include "raylib.h"

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
    
    particle particles[3];
    particles[0].position = Vector2(0., 0.);
    particles[1].position = Vector2(10., 15.);
    particles[2].position = Vector2(35., 35.);

    particles[0].radius = 1.;
    particles[1].radius = 3.;
    particles[2].radius = 5.;

    particles[0].colour = MAROON;
    particles[1].colour = RED;
    particles[2].colour = BLACK;
    
    // When
    //DrawCircle(0, 0, 1., MAROON);
    //DrawCircle(10, 15, 3., RED);
    //DrawCircle(35, 35, 5., BLACK);
    displayParticle(particles);

    // Then
    ASSERT_EQ(3, DrawCircle_fake.call_count);

    // 1st Call
    ASSERT_EQ(0, DrawCircle_fake.arg0_history[0]);
    ASSERT_EQ(0, DrawCircle_fake.arg1_history[0]);
    ASSERT_EQ(1., DrawCircle_fake.arg2_history[0]);
    ASSERT_TRUE(colorsEqual(MAROON, DrawCircle_fake.arg3_history[0]));

    // 2nd Call
    ASSERT_EQ(10, DrawCircle_fake.arg0_history[1]);
    ASSERT_EQ(15, DrawCircle_fake.arg1_history[1]);
    ASSERT_EQ(3., DrawCircle_fake.arg2_history[1]);
    ASSERT_TRUE(colorsEqual(RED, DrawCircle_fake.arg3_history[1]));

    // 3rd Call
    ASSERT_EQ(35, DrawCircle_fake.arg0_history[2]);
    ASSERT_EQ(35, DrawCircle_fake.arg1_history[2]);
    ASSERT_EQ(5., DrawCircle_fake.arg2_history[2]);
    ASSERT_TRUE(colorsEqual(BLACK, DrawCircle_fake.arg3_history[2]));
}
   
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}