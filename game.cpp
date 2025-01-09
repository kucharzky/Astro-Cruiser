#include "game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Draw()
{
	spaceship.Draw();

	for (auto& p : spaceship.projectiles) p.Draw();
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
	for (auto i = spaceship.projectiles.begin(); i != spaceship.projectiles.end();)
	{
		if (!i->shot) spaceship.projectiles.erase(i);
		else ++i;
	}
}
