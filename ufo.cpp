#include "ufo.h"


UFO::UFO()
{
	texture = LoadTexture("textures/ufo.png");
	spawned = false;
}

UFO::~UFO()
{
	UnloadTexture(texture);
}


void UFO::SpawnUFO()
{
	position.y = 90;
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dis(0, 1);
	int random = dis(rng);
	if (random == 0) {
		position.x = 0;
		speed = 3;
	}
	else {
		position.x = GetScreenWidth() - texture.width;
		speed = -3;
	}
	spawned = true;
}

Rectangle UFO::GetHitbox()
{
	if(spawned) return { position.x, position.y, float(texture.width), float(texture.height) };
	else return { 0,0,0,0};
}

void UFO::Update()
{
	if (spawned) {
		position.x += speed;
		if (position.x < 0|| position.x > GetScreenWidth() - texture.width) {
			spawned = false;
		}
	}
}

void UFO::Draw()
{
	if (spawned) {
		DrawTextureV(texture, position, WHITE);
	}
}
