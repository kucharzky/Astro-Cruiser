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
	Vector2 GetPosition();
	void UnloadTexture();
private:
	Texture2D texture;
	Vector2 position;
	int speed;
};