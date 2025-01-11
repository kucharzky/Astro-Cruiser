#include "game.h"

Game::Game()
{
	asteroids = InitAsteroids();
	enemies = InitEnemies();
}

Game::~Game()
{

}

void Game::Draw()
{
	spaceship.Draw();

	for (auto& sp : spaceship.projectiles) sp.Draw();

	for (auto& a : asteroids) a.Draw();

	for (auto& e : enemies) e.Draw();
}

void Game::Update()
{
	for (auto& p : spaceship.projectiles) p.Update();
	OutOfScreen();
}

void Game::Inputs()
{
	if (IsKeyDown(KEY_LEFT)) spaceship.MoveL();
	if (IsKeyDown(KEY_RIGHT)) spaceship.MoveR();
	//if (IsKeyPressed(KEY_SPACE)) spaceship.Fire();
	if (IsKeyDown(KEY_SPACE)) spaceship.Fire();
}

void Game::OutOfScreen() // Usuwanie pocisków poza ekranem
{
	for (auto p = spaceship.projectiles.begin(); p != spaceship.projectiles.end();)
	{
		if (!p->shot)
			p = spaceship.projectiles.erase(p);
		else
			++p;
	}
}

std::vector<Asteroid> Game::InitAsteroids()
{
	int asteroidWidth = Asteroid::mesh[0].size() * 4;
	float jump2next = (GetScreenWidth() - (asteroidWidth*5)) / 6;
	for (int i{ 0 }; i < 5; i++)
	{
		float offset2next = (i + 1) * jump2next + i * asteroidWidth;
		asteroids.push_back(Asteroid({ offset2next, float(GetScreenHeight() - 200 )}));
	}
	return asteroids;
}

std::vector<Enemy> Game::InitEnemies()
{
	std::vector<Enemy> enemies;
	for (int i{ 0 }; i < 5; i++)
	{
		for (int j{ 0 }; j < 11; j++)
		{
			int enemyType;
			if (i < 1) enemyType = 3;
			else if (i < 3) enemyType = 2;
			else enemyType = 1;
			float x = 340 + j * 55;
			float y = 110 + i * 55;
			enemies.push_back(Enemy(enemyType, { x,y }));
		}
	}
	return enemies;
}
