#pragma once
#include <raylib.h>

class Enemy 
{
public:
	Enemy(int enemyType,Vector2 position);
	void Draw();
	int enemyType;
	Vector2 position;
	Texture2D texture;
	void Update();
	int GetType();
private:

};