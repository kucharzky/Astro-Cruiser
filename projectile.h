#pragma once
#include <raylib.h>
/// <>
/// Klasa Projectile - odpowiada za strzaly ktore sa wystrzeliwywane przez gracza lub przeciwnikow
/// Konstruktor - definiujemy miejsce z ktorego zaczyna leciec pocisk, jego predkosc czyli ile pikseli na sekunde
/// bedzie sie przemieszczac oraz czy dany pocisk zostal wystrzelony przez gracza
/// </>
class Projectile
{
public:
	Projectile(Vector2 position, float speed, bool isPlayerShot);
	~Projectile();
	void Update();
	void Draw();
	bool shot;
	static void UnloadTextures();
	static Texture2D textures[2]; // 0 - pocisk gracza, 1 - pocisk wroga
	Rectangle GetHitbox();
private:
	Vector2 position;
	float speed;
	bool isPlayerShot; // flaga okreslajaca czy pocisk nalezy do gracza
};