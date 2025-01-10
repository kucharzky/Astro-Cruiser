#include "game.h"

Game::Game()
{
	asteroids = InitAsteroids();
}

Game::~Game()
{

}

void Game::Draw()
{
	spaceship.Draw();

	for (auto& sp : spaceship.projectiles) sp.Draw();

	for (auto& a : asteroids) a.Draw();
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
	for (int i = 0; i < 5; i++)
	{
		float offset2next = (i + 1) * jump2next + i * asteroidWidth;
		asteroids.push_back(Asteroid({ offset2next, float(GetScreenHeight() - 200 )}));
	}
	return asteroids;
}
