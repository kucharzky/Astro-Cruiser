#include "game.h"
#include <random>
#include <iostream>

std::mt19937 rng(std::random_device{}());
Game::Game()
{
	asteroids = InitAsteroids();
	enemies = InitEnemies();
	enemiesCourse = 2;
	//wartosci domysle
	enemySpeed = 2;
	enemyDownSpeed = 4;
	lastEnemyFire = 0.0;
	lastUfo = 0.0;
	std::uniform_int_distribution<int> dist(10, 20);
	ufoCooldown = dist(rng);
}

Game::~Game()
{
	Enemy::KillEnemy();
	Projectile::UnloadTextures();
}

void Game::Draw()
{
	spaceship.Draw();
	for (auto& a : asteroids) a.Draw();
	for (auto& e : enemies) e.Draw();
	for (auto& p : spaceship.projectiles) p.Draw();
	for (auto& p : enemiesProjectiles) p.Draw(); // Rysowanie pocisków wrogów
	ufo.Draw();
}

void Game::Update()
{
	double currentTime = GetTime();
	for (auto& p : spaceship.projectiles) p.Update();
	for (int i = 0; i < spaceship.projectiles.size(); i++)
	{
		if (!spaceship.projectiles[i].shot)
		{
			spaceship.projectiles.erase(spaceship.projectiles.begin() + i);
			i--;
		}
	}

	for (auto& p : enemiesProjectiles) p.Update(); // Uruchomienie metody Update() dla pocisków wrogów
	for (int i = 0; i < enemiesProjectiles.size(); i++)
	{
		if (!enemiesProjectiles[i].shot)
		{
			enemiesProjectiles.erase(enemiesProjectiles.begin() + i);
			i--;
		}
	}
	if (currentTime - lastUfo > ufoCooldown)
	{
		ufo.SpawnUFO();
		lastUfo = GetTime();
		std::uniform_int_distribution<int> dist(10, 20);
		ufoCooldown = dist(rng);
	}
	EnemyFire();
	UpdateEnemies();
	//OutOfScreen();
	ufo.Update();
	CollisionsCheck();
}

void Game::Inputs()
{
	if (IsKeyDown(KEY_LEFT)) spaceship.MoveL();
	if (IsKeyDown(KEY_RIGHT)) spaceship.MoveR();
	//if (IsKeyPressed(KEY_SPACE)) spaceship.Fire(); - zamiast tego dodalem delay do strzalow
	if (IsKeyDown(KEY_SPACE)) spaceship.Fire();
}

void Game::SetEnemiesSpeed(int speed)
{
	this->enemySpeed = speed;
}

int Game::GetEnemiesSpeed()
{
	return enemySpeed;
}

void Game::SetEnemiesDownSpeed(int speed)
{
	this->enemyDownSpeed = speed;
}

int Game::GetEnemiesDownSpeed()
{
	return enemyDownSpeed;
}

int Game::GetSizeOfEnemies()
{
	return enemies.size();
}

//void Game::OutOfScreen() // usuwanie pocisków poza ekranem
//{
//	for (auto p = spaceship.projectiles.begin(); p != spaceship.projectiles.end();)
//	{
//		if (!p->shot)
//			p = spaceship.projectiles.erase(p);
//		else
//			++p;
//	}
//}

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

void Game::CollisionsCheck()
{
	// KOLIZJE PRZECIWNIKOW Z GRACZEM
	for (auto& ep : enemiesProjectiles)
	{
		if (CheckCollisionRecs(ep.GetHitbox(), spaceship.GetHitbox()))
		{
			ep.shot = false;
			std::cout << "kolizja ze strzalem wroga" << std::endl;
		}
		for (auto& a : asteroids) // Kolizje strzalow z asteroidami
		{
			auto i = a.decays.begin();
			while (i != a.decays.end())
			{
				if (CheckCollisionRecs(ep.GetHitbox(), i->GetHitbox()))
				{
					i = a.decays.erase(i);
					ep.shot = false;
				}
				else ++i;

			}
		}
	}
	for (auto& e : enemies)
	{
		for (auto& a : asteroids) // Kolizje przeciwnikow z asteroidami
		{
			auto i = a.decays.begin();
			while (i != a.decays.end())
			{
				if (CheckCollisionRecs(e.GetHitbox(), i->GetHitbox())) i = a.decays.erase(i);
				else ++i;
			}
		}
		if (CheckCollisionRecs(e.GetHitbox(), spaceship.GetHitbox())) // Kolizje przeciwnikow z graczem
		{
			std::cout << "bezposrednia kolizja z wrogiem" << std::endl;
		}
	}
	// KOLIZJE GRACZA Z PRZECIWNIKAMI
    for (auto& sp : spaceship.projectiles)
    {
        auto i = enemies.begin();
        while (i != enemies.end())
        {
            if (CheckCollisionRecs(sp.GetHitbox(), i->GetHitbox()))
            {
                i = enemies.erase(i);
                sp.shot = false;
            }
            else
            {
                ++i;
            }
        }
		for (auto& a : asteroids) // Kolizje strzalow z asteroidami
        {
            auto i = a.decays.begin();
            while (i != a.decays.end())
            {
                if (CheckCollisionRecs(sp.GetHitbox(), i->GetHitbox()))
                {
                    i = a.decays.erase(i);
                    sp.shot = false;
                }
                else
                {
                    ++i;
                }
            }
        }
        if (CheckCollisionRecs(ufo.GetHitbox(), sp.GetHitbox()))
        {
            ufo.spawned = false;
            sp.shot = false;
        }
    }
	
}

void Game::EnemyFire()
{
	std::uniform_int_distribution<int> dist(0, GetSizeOfEnemies() - 1);
    float currentTime = GetTime();
    if (currentTime - lastEnemyFire >= enemyFireCooldown && enemies.size() > 0) {
		int random = dist(rng);
        Enemy& enemy = enemies[random];
        enemiesProjectiles.push_back(Projectile({ enemy.GetPosition().x + enemy.textures[enemy.GetType() - 1].width / 2 - 3, enemy.GetPosition().y + enemy.textures[enemy.GetType() - 1].height }, 5, false));
        lastEnemyFire = currentTime;
    }
}

void Game::UpdateEnemies()
{
	for (auto& e : enemies)
	{
		if (e.GetPosition().x + e.textures[e.GetType()-1].width > GetScreenWidth())
		{
			enemiesCourse = -GetEnemiesSpeed(); // Zmiana kierunku
			MoveDown();
		}
		if (e.GetPosition().x < 0) {
			enemiesCourse = GetEnemiesSpeed();
			MoveDown();
		}

		e.Update(enemiesCourse);
	}
}

void Game::MoveDown()
{
	for (auto& e : enemies) e.position.y += GetEnemiesDownSpeed();
}
