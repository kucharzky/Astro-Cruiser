#pragma once
#include <raylib.h>
#include "projectile.h"
#include <vector>
class Player
{
public:
	Player();
	~Player();
	Rectangle GetHitbox();
	Vector2 GetPosition();
	void MoveL();
	void MoveR();
	void Fire();
	void Draw();
	std::vector<Projectile> projectiles;
	void UnloadResources();
	void ResetPlayer();
	Texture2D GetTexture();
private:
	Texture2D texture;
	Vector2 position;
	float lastActive;
	Sound sound;
};