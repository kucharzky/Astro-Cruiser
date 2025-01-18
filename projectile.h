#pragma once
#include <raylib.h>
class Projectile
{
public:
	Projectile(Vector2 position, float speed, bool isPlayerShot);
	~Projectile();
	void Update();
	void Draw();
	bool shot;
	static void UnloadTextures();
	static Texture2D textures[2]; // 0 - pocisk gracza, 1 - pocisk wroga
private:
	Vector2 position;
	float speed;
	bool isPlayerShot; // flaga okreslajaca czy pocisk nalezy do gracza
};