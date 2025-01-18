#include "player.h"

Player::Player()
{
	texture = LoadTexture("textures/ship_2.png");
	sound = LoadSound("sounds/gunshot.wav");
    position = { static_cast<float>(GetScreenWidth()/2 - texture.width/2), static_cast<float>(GetScreenHeight() - 1.5*texture.height) };
	lastActive = 0.0;
}

Player::~Player()
{
	UnloadTexture(texture);
	UnloadSound(sound);
}

Rectangle Player::GetHitbox()
{
	return { position.x, position.y, float(texture.width), float(texture.height) };
}

void Player::MoveL()
{
	position.x -= 5;	
	if (position.x <= 0) position.x = 0;
}

void Player::MoveR()
{
	position.x += 5;
	if (position.x >= GetScreenWidth() - texture.width) position.x = GetScreenWidth() - texture.width;
}

void Player::Fire()
{
	if (GetTime() - lastActive < 0.5) return;
	projectiles.push_back(Projectile({ position.x + texture.width / 2 - 3, position.y  }, 10, true));
	lastActive = GetTime();
	PlaySound(sound);
}

void Player::Draw()
{
	DrawTextureV(texture, position, WHITE);
}
