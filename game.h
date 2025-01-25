#pragma once
#include "player.h"
#include "asteroid.h"
#include "enemy.h"
#include "ufo.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <filesystem>

void SaveScore(int score);
std::vector<int> LoadScores();
int GetHighScore();

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void Inputs();
	void SetEnemiesSpeed(int speed);
	int GetEnemiesSpeed();
	int GetEnemiesDownSpeed();
	size_t GetSizeOfEnemies();
	void SetLives(int lives);
	int GetLives();
	bool isGameRunning;
	int playerScore;
	int waveCounter;
	bool isPaused;
	void TogglePause();
	Music mainMenuMusic;
	Music gameplayMusic;
private:
	Player cruiser;
	int lives;
	void DeathScreen();
	void ClearObjects();
	void InitGame();
	Texture2D explosion;
	Sound explosionSound;
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
	int enemiesCourse;
	int enemySpeed;
	int enemyDownSpeed;
	UFO ufo;
	float ufoCooldown;
	double lastUfo;
	bool isImmune;
	double immunityTime;
	const double immunityDuration{ 2.0 };
	const float barrierRadius = 40.0f;
	const Color barrierColor = { 175,238,238,128 };
	
};