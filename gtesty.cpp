#include "gtest/gtest.h"
#include "player.h" 

TEST(PlayerTest, MovementTest) {
    Player player;

    Vector2 initialPosition = player.GetPosition();

    player.MoveL();

    EXPECT_LT(player.GetPosition().x, initialPosition.x);

    player.MoveR();

    EXPECT_FLOAT_EQ(player.GetPosition().x, initialPosition.x);
}