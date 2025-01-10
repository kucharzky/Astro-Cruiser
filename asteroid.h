#pragma once
#include <vector>
#include "decay.h"

class Asteroid
{
public:
	Asteroid(Vector2 position);
	void Draw();
	Vector2 position;
	std::vector<Decay> decays;
	static std::vector<std::vector<int>> mesh;
private:
};