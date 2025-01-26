#pragma once
#include <raylib.h>
/// <>
/// Klasa button - uzywana w menu glownym, creditsach oraz w przypadku pauzy, wywolywana jest jakas funkcja gdy nastapi kolizja cursora gracza z
/// z tekstura
/// Konstruktor - podajemy lokalizacje pliku, miejsce w ktorym ma sie znajdowac przycisk oraz jest opcja przeskalowania wielkosci
/// IsPressed() - sprawdzenie pozycji kursora oraz czy lewy przycisk myszy zostal wcisniety
/// </>
class Button
{
public:
	Button(const char* imagePath, Vector2 imagePosition, float scale);
	~Button();
	void Draw();
	bool isPressed(Vector2 mousePos, bool mousePressed);
private:
	Texture2D texture;
	Vector2 position;
};