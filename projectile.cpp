#include "projectile.h"

Projectile::Projectile(Vector2 position, float speed)
{
	texture = LoadTexture("txts/shot.png");
	this->position = position;
	this->speed = speed;
	shot = true;
}

Projectile::~Projectile()
{
}

void Projectile::Draw()
{
	if (shot) DrawTextureV(texture, position, WHITE);
}

void Projectile::Update()
{
	position.y -= speed;
	if (shot)
	{
		if (position.y > GetScreenHeight() || position.y < 0) shot = false;
	}
}