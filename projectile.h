#pragma once
#include <raylib.h>
class Projectile
{
public:
	Projectile(Vector2 position, float speed);
	~Projectile();
	void Update();
	void Draw();
	bool shot;
private:
	Texture2D texture;
	Vector2 position;
	float speed;
};