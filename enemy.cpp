#include "enemy.h"

Enemy::Enemy(int enemyType, Vector2 position)
{
	this->enemyType = enemyType;
	this->position = position;
	if (enemyType == 1)
	{
		texture = LoadTexture("textures/alien1.png");
	}
	else if (enemyType == 2)
	{
		texture = LoadTexture("textures/alien2.png");
	}
	else if (enemyType == 3)
	{
		texture = LoadTexture("textures/alien3.png");
	}
}

void Enemy::Draw()
{
	DrawTextureV(texture, position, WHITE);
}

int Enemy::GetType()
{
	return enemyType;
}
