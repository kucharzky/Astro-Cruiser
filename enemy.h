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
private:
	int enemyType;
	Vector2 position;
	static bool texturesLoaded;

};