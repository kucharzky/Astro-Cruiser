#include "decay.h"
#include <random>
Decay::Decay(Vector2 position) : position(position)
{
}
void Decay::Draw()
{
	DrawRectangle(position.x, position.y, 4, 4, { 130,130,130,170 });
}

Rectangle Decay::GetHitbox()
{
	return { position.x, position.y, 4, 4 };
}
