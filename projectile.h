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
	static void UnloadTexture();
	static Texture2D texture;
private:

	Vector2 position;
	float speed;
};