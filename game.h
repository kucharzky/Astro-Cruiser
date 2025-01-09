#pragma once
#include "player.h"

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
};