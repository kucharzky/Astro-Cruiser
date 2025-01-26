#pragma once
#include <raylib.h>
#include "projectile.h"
#include <vector>
/// <>
/// Klasa Player - obiekt gracza, odpowiada za sterowanie, wystrzeliwywanie pociskow
/// GetHitbox(),GetPosition(),UnloadResources(),Draw() - analogicznie jak w ufo.h
/// MoveL() - przesuwa gracza o dana wartosc pikseli w lewo
/// MoveR() - przesuwa obiekt gracza w prawo
/// Fire() - cooldown na strzelanie, dodanie pocisku do wektora, wlaczenie dzwieku
/// </>
class Player
{
public:
	Player();
	~Player();
	Rectangle GetHitbox();
	Vector2 GetPosition();
	void MoveL();
	void MoveR();
	void Fire();
	void Draw();
	std::vector<Projectile> projectiles;
	void UnloadResources();
	void ResetPlayer();
	Texture2D GetTexture();
private:
	Texture2D texture;
	Vector2 position;
	float lastActive;
	Sound sound;
};