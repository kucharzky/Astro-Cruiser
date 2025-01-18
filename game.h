#pragma once
#include "player.h"
#include "asteroid.h"
#include "enemy.h"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void Inputs();
private:
	Player spaceship;
	void OutOfScreen();
	std::vector<Asteroid> asteroids;
	std::vector<Asteroid> InitAsteroids();
	std::vector<Enemy> enemies;
	std::vector<Enemy> InitEnemies();
	void UpdateEnemies();
	void DownMovement();
	int enemiesCourse;
};