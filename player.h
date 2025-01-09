#pragma once
#include <raylib.h>
#include "projectile.h"
#include <vector>
class Player
{
public:
	Player();
	~Player();
	void MoveL();
	void MoveR();
	void Fire();
	void Draw();
	std::vector<Projectile> projectiles;
private:
	Texture2D texture;
	Vector2 position;
	float lastActive;
};