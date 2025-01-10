#pragma once
#include "player.h"
#include "asteroid.h"

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
};