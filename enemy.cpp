#include "enemy.h"
Texture2D Enemy::textures[3] = {};
bool Enemy::texturesLoaded = false;
// 
Enemy::Enemy(int enemyType, Vector2 position)
{
	this->enemyType = enemyType;
	this->position = position;
	if (!texturesLoaded)
	{
		textures[0] = LoadTexture("textures/alien1.png");
		textures[1] = LoadTexture("textures/alien2.png");
		textures[2] = LoadTexture("textures/alien3.png");
		texturesLoaded = true;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	DrawTextureV(textures[enemyType-1], position, WHITE);
}

void Enemy::KillEnemy()
{
	if (texturesLoaded)
	{
		for (auto& t : textures) UnloadTexture(t);
		texturesLoaded = false;
	}
}

int Enemy::GetType()
{
	return enemyType;
}

Vector2 Enemy::GetPosition()
{
	return position;
}
void Enemy::Update(int course)
{
	position.x += course;

}

Rectangle Enemy::GetHitbox()
{
	return { position.x, position.y, float(textures[enemyType - 1].width), float(textures[enemyType - 1].height) };
}
