#include "include/test/fff.h"
#include "gtest/googletest/include/gtest/gtest.h"
#include "include/raylib.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(DrawCircle, int, int, float, Color);

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
    /*
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
    */
    // Expect
    //::testing::Sequence s;
    //EXPECT_CALL(raylibMock, DrawCircle(0, 0, 1., MAROON)).InSequence(s);
    //EXPECT_CALL(raylibMock, DrawCircle(10, 15, 3., RED)).InSequence(s);
    //EXPECT_CALL(raylibMock, DrawCircle(35, 35, 5., BLACK)).InSequence(s);

    // Verify that DrawCircle is called exactly 3 times
    //EXPECT_CALL(raylibMock, DrawCircle).Times(3);

    // When
    //DrawCircle(0, 0, 1., MAROON);
    //DrawCircle(10, 15, 3., RED);
    //DrawCircle(35, 35, 5., BLACK);

    //displayParticle(particles);
}
   
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}