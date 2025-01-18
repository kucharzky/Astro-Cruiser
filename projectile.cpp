#include "projectile.h"

Texture2D Projectile::texture = {};

Projectile::Projectile(Vector2 position, float speed)
{
	if (texture.id == 0) texture = LoadTexture("textures/shot.png");
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

void Projectile::UnloadTexture()
{
	if (texture.id != 0) {
		::UnloadTexture(texture); // Use the global UnloadTexture function
		texture = {};
	}
}

void Projectile::Update()
{
	position.y -= speed;
	if (shot)
	{
		if (position.y > GetScreenHeight() || position.y < 0) shot = false;
	}
}