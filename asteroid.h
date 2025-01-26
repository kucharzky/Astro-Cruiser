#pragma once
#include <vector>
#include "decay.h"
/// <>
/// Klasa Asteroid - reprezentuje bariery za ktorymi mozemy sie chowac i unikac pociskow przeciwnikow
/// W konstruktorze w miejscu ktore zdefiniuejmy wedlug mesha narysujemy asteroide skladajaca sie z malych bloczkow
/// zdefiniowanych w decay
/// Klasa draw wykonuje polecenie rysowania dla wszystkich pomniejszych elementow w meshu
/// </>
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