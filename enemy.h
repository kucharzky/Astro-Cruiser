#pragma once
#include <raylib.h>

class Enemy 
{
public:
	Enemy(int enemyType,Vector2 position);
	~Enemy();
	void Draw();
	static void KillEnemy();
	int GetType();
	Vector2 GetPosition();
	void Update(int course);
	static Texture2D textures[3];
	Vector2 position;
	Rectangle GetHitbox();
private:
	int enemyType;
	static bool texturesLoaded;

};