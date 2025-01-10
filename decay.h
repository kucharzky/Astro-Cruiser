#pragma once
#include <raylib.h>

class Decay
{
public:
	Decay(Vector2 position);
	void Draw();
private:
	Vector2 position;
};