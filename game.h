#pragma once
#include "player.h"
#include "asteroid.h"
#include "enemy.h"
#include "ufo.h"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void Inputs();
	void SetEnemiesSpeed(int speed);
	int GetEnemiesSpeed();
	void SetEnemiesDownSpeed(int speed);
	int GetEnemiesDownSpeed();
	size_t GetSizeOfEnemies();
	void SetLives(int lives);
	int GetLives();
	bool isGameRunning;
private:
	Player cruiser;
	int lives;
	void DeathScreen();
	void ClearObjects();
	void InitGame();
	Texture2D explosion;
	//void OutOfScreen();
	std::vector<Asteroid> asteroids;
	std::vector<Asteroid> InitAsteroids();
	std::vector<Enemy> enemies;
	std::vector<Enemy> InitEnemies();
	std::vector<Projectile> enemiesProjectiles;
	void CollisionsCheck();
	void EnemyFire();
	constexpr static float enemyFireCooldown{ 0.5 };
	float lastEnemyFire;
	void UpdateEnemies();
	void MoveDown();
	int enemiesCourse;
	int enemySpeed;
	int enemyDownSpeed;
	UFO ufo;
	float ufoCooldown;
	double lastUfo;
};