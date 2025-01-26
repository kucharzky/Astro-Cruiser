#pragma once
#include <raylib.h>
/// <>
/// Klasa Enemy - reprezentuje przeciwnikow do ktorych strzelamy i za ktore dostajemy punkty
/// Konstruktor - specyfikacja typu przeciwnika oraz pozycji w ktorej zostanie przywolany
/// KillEnemy() - rozladowanie tekstur dla wszystkich przeciwnikow
/// GetType() - zwraca typ przeciwnika którego przywolalismy - inna tekstura inna punktacja dla roznych przeciwnikow
/// </>
class Enemy 
{
public:
	Enemy(int enemyType,Vector2 position);
	~Enemy();
	void Draw();
	static void KillEnemy();
	int GetType();
	Vector2 GetPosition();
	void Update(int course);
	static Texture2D textures[3];
	Vector2 position;
	Rectangle GetHitbox();
private:
	int enemyType;
	static bool texturesLoaded;

};