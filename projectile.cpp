#include "projectile.h"

Texture2D Projectile::textures[2] = {}; // statyczna tablica tekstur

Projectile::Projectile(Vector2 position, float speed, bool isPlayerShot)
{
	if (textures[0].id == 0) textures[0] = LoadTexture("textures/shot.png"); // wczytanie tekstury dla gracza
	if (textures[1].id == 0) textures[1] = LoadTexture("textures/enemyshot.png"); //wczytanie tekstury dla wroga
	this->position = position;
	this->speed = speed;
	this->isPlayerShot = isPlayerShot;
	shot = true;
}

Projectile::~Projectile()
{
}

void Projectile::Draw()
{
	if (shot) {
		if (isPlayerShot) {
			DrawTextureV(textures[0], position, WHITE);
		}
		else {
			DrawTextureV(textures[1], position, WHITE);
		}
	}
}

void Projectile::UnloadTextures()
{
	if (textures[0].id != 0) {
		::UnloadTexture(textures[0]);
		textures[0] = {};
	}
	if (textures[1].id != 0) {
		::UnloadTexture(textures[1]);
		textures[1] = {};
	}
}

Rectangle Projectile::GetHitbox()
{
	return { position.x, position.y, float(textures[0].width), float(textures[0].height) };
}

void Projectile::Update()
{
	if (isPlayerShot) {
		position.y -= speed; // strzal gracza leci w gore
	}
	else {
		position.y += speed; // strzal wroga leci w dol
	}

	if (shot)
	{
		if (position.y > GetScreenHeight() || position.y < 0) shot = false;
	}
}