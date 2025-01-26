#pragma once
#include "raylib.h"
#include <random>
/// <>
/// Klasa ufo - specjalny przeciwnik warty wiecej punktów
/// Draw() - zaladowanie tekstury z pliku, ustalenie pozycji
/// Update() - poruszanie sie przeciwnika, sprawdzenie czy dotknal rogu ekranu - zmiana flagi spawned na false
/// SpawnUFO() - zdefiniowanie wysokosci na ekranie na ktorej sie pojawi, randomizacja miejsca pojawienia sie, zmiana flagi spawned na true
/// GetHitbox() - zwraca pozycje prostkata tekstury
/// GetPostion() - pozycja statku ufo
/// UnloadTexture() - rozladowanie tekstury
/// </>
class UFO {
public:
	UFO();
	~UFO();
	void Draw();
	void Update();
	void SpawnUFO();
	bool spawned;
	Rectangle GetHitbox();
	Vector2 GetPosition();
	void UnloadTexture();
private:
	Texture2D texture;
	Vector2 position;
	int speed;
};