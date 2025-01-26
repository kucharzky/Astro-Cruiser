#pragma once
#include <raylib.h>
/// <>
/// Klasa Decay - reprezentuje mniejsze bloczki z ktorych stworzona jest klasa asteroid
/// </>
class Decay
{
public:
	Decay(Vector2 position);
	void Draw();
	Rectangle GetHitbox();
private:
	Vector2 position;
};