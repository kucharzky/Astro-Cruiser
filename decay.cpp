#include "decay.h"

Decay::Decay(Vector2 position)
{
	this->position = position;
}
void Decay::Draw()
{
	//DrawRectangle(position.x, position.y, 4, 4, {255,0,0,255});
	DrawRectangle(position.x, position.y, 4, 4, GRAY);
}

Rectangle Decay::GetHitbox()
{
	return { position.x, position.y, 4, 4 };
}
