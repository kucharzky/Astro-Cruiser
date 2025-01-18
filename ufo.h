#pragma once
#include "raylib.h"
#include <random>

class UFO {
public:
	UFO();
	~UFO();
	void Draw();
	void Update();
	void SpawnUFO();
	bool spawned;
	Rectangle GetHitbox();
private:
	Texture2D texture;
	Vector2 position;
	int speed;
};