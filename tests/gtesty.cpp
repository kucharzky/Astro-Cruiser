#include "gtest/gtest.h"
//#include "player.h"
//#include "projectile.h"
//#include "enemy.h"
//#include "asteroid.h"
//#include "ufo.h"
#include "game.h"
#include <raylib.h>

//////////////////////////
// TESTY GRACZA
/////////////////////////

TEST(PlayerTest, PlayerInitialization) {
    Player player;
    EXPECT_EQ(player.GetPosition().x, GetScreenWidth() / 2 - player.GetTexture().width / 2);
    EXPECT_EQ(player.GetPosition().y, GetScreenHeight() - 1.5 * player.GetTexture().height - 30);
    EXPECT_TRUE(player.GetTexture().id != 0); // Sprawdzenie, czy tekstura zostala zaladowana
}

TEST(PlayerTest, PlayerMovement) {
    Player player;
    Vector2 initialPosition = player.GetPosition();
    player.MoveL();
    EXPECT_LT(player.GetPosition().x, initialPosition.x);
    player.MoveR();
    EXPECT_FLOAT_EQ(player.GetPosition().x, initialPosition.x);
    player.MoveR();
    initialPosition = player.GetPosition();
    for (int i = 0; i < 300; i++) player.MoveR(); //Poruszanie sie w prawo az do kranca ekranu
    EXPECT_EQ(player.GetPosition().x, GetScreenWidth() - player.GetTexture().width);
}

TEST(PlayerTest, PlayerFire) {
    Player player;
    int initialProjectilesSize = player.projectiles.size();
    player.Fire();
    EXPECT_EQ(player.projectiles.size(), initialProjectilesSize + 1);
    player.Fire();
    EXPECT_EQ(player.projectiles.size(), initialProjectilesSize + 1); // Sprawdzenie cooldownu
    //Symulacja odczekania
    double startTime = GetTime();
    while (GetTime() - startTime < 0.6) {}
    player.Fire();
    EXPECT_EQ(player.projectiles.size(), initialProjectilesSize + 2); // Po odczekaniu mozna oddac kolejny strzal
}

TEST(PlayerTest, PlayerReset) {
    Player player;
    player.Fire();
    player.ResetPlayer();
    EXPECT_EQ(player.GetPosition().x, GetScreenWidth() / 2 - player.GetTexture().width / 2);
    EXPECT_EQ(player.GetPosition().y, GetScreenHeight() - 1.5 * player.GetTexture().height - 30);
    EXPECT_TRUE(player.projectiles.empty());
}

//////////////////////////
// TESTY POCISKOW
/////////////////////////

TEST(ProjectileTest, ProjectileInitialization) {
    Vector2 pos = { 100, 200 };
    float speed = 5.0f;
    Projectile p1(pos, speed, true);
    Projectile p2(pos, speed, false);

    EXPECT_EQ(p1.GetHitbox().x, pos.x);
    EXPECT_EQ(p1.GetHitbox().y, pos.y);
    EXPECT_EQ(p2.GetHitbox().x, pos.x);
    EXPECT_EQ(p2.GetHitbox().y, pos.y);
    EXPECT_TRUE(p1.shot);
    EXPECT_TRUE(p2.shot);
}

TEST(ProjectileTest, ProjectileUpdate) {
    Vector2 initialPos = { 100, 200 };
    float speed = 5.0f;
    Projectile playerProjectile(initialPos, speed, true);
    Projectile enemyProjectile(initialPos, speed, false);

    playerProjectile.Update();
    EXPECT_LT(playerProjectile.GetHitbox().y, initialPos.y); // Pocisk gracza leci w góre

    enemyProjectile.Update();
    EXPECT_GT(enemyProjectile.GetHitbox().y, initialPos.y); // Pocisk wroga leci w dól
}

//////////////////////////
// TESTY PRZECIWNIKOW
/////////////////////////

TEST(EnemyTest, EnemyInitialization) {
    Enemy enemy(1, { 50, 50 });
    EXPECT_EQ(enemy.GetType(), 1);
    EXPECT_EQ(enemy.GetPosition().x, 50);
    EXPECT_EQ(enemy.GetPosition().y, 50);
    EXPECT_TRUE(enemy.textures[0].id != 0);
    EXPECT_TRUE(enemy.textures[1].id != 0);
    EXPECT_TRUE(enemy.textures[2].id != 0);
}

TEST(EnemyTest, EnemyUpdate) {
    Enemy enemy(1, { 50, 50 });
    Vector2 initialPosition = enemy.GetPosition();
    enemy.Update(2);
    EXPECT_EQ(enemy.GetPosition().x, initialPosition.x + 2);
}

//////////////////////////
// TESTY ASTEROID
/////////////////////////

TEST(AsteroidTest, AsteroidInitialization) {
    Asteroid asteroid({ 100, 200 });
    EXPECT_EQ(asteroid.position.x, 100);
    EXPECT_EQ(asteroid.position.y, 200);
    EXPECT_FALSE(asteroid.decays.empty());
}

//////////////////////////
// TESTY UFO
/////////////////////////

TEST(UFOTest, UfoSpawn) {
    UFO ufo;
    ufo.SpawnUFO();
    EXPECT_TRUE(ufo.GetPosition().y == 90);
    EXPECT_TRUE(ufo.GetPosition().x == 0 || ufo.GetPosition().x == GetScreenWidth() - ufo.GetHitbox().width);
}

TEST(UFOTest, UfoUpdate) {
    UFO ufo;
    ufo.SpawnUFO();
    Vector2 initialPosition = ufo.GetPosition();
    ufo.Update();
    if (initialPosition.x == 0) {
        EXPECT_GT(ufo.GetPosition().x, initialPosition.x);
    }
    else {
        EXPECT_LT(ufo.GetPosition().x, initialPosition.x);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}