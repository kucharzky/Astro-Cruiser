#include "game.h"

void SaveScore(int score)
{
	std::filesystem::create_directory("saves"); // Ensure the directory exists
	std::ofstream file("saves/scores.txt", std::ios::app);
	if (file.is_open())
	{
		file << score << std::endl;
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for writing scores." << std::endl;
	}
}

std::vector<int> LoadScores()
{
	std::vector<int> scores;
	std::ifstream file("saves/scores.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			int score;
			ss >> score;
			scores.push_back(score);
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for reading scores." << std::endl;
	}
	return scores;
}

int GetHighScore()
{
	std::vector<int> scores = LoadScores();
	if (!scores.empty())
	{
		return *std::max_element(scores.begin(), scores.end());
	}
	return 0; // Return 0 if no scores are found
}

std::mt19937 rng(std::random_device{}());
Game::Game()
{
	explosion = LoadTexture("textures/explosion2.png");
	asteroids = InitAsteroids();
	enemies = InitEnemies();
	enemiesCourse = 1;
	//wartosci domyslne
	waveCounter = 0;
	playerScore = 0;
	lives = 3;
	enemySpeed = 1;
	enemyDownSpeed = 4;
	lastEnemyFire = 0.0;
	lastUfo = 0.0;
	std::uniform_int_distribution<> dist(10, 20);
	ufoCooldown = dist(rng);
	isGameRunning = true;
	isImmune = false;
	immunityTime = 0.0;
	isPaused = false;
}

Game::~Game()
{
	Enemy::KillEnemy();
	Projectile::UnloadTextures();
	ufo.UnloadTexture();
	cruiser.UnloadResources();
	::UnloadTexture(explosion);
}

void Game::Draw()
{
	cruiser.Draw();
	for (auto& a : asteroids) a.Draw();
	for (auto& e : enemies) e.Draw();
	for (auto& cp : cruiser.projectiles) cp.Draw();
	for (auto& p : enemiesProjectiles) p.Draw();
	ufo.Draw();
	if (isImmune&&isGameRunning) DrawCircleV({cruiser.GetPosition().x + cruiser.GetTexture().width/2,cruiser.GetPosition().y + cruiser.GetTexture().height/2}, barrierRadius, barrierColor);
}

void Game::Update()
{
	if (isPaused)return;
	if (isGameRunning) {
		double currentTime = GetTime();
		if (isImmune && (currentTime - immunityTime >= immunityDuration)) {
			isImmune = false;
		}
		for (auto& cp : cruiser.projectiles) cp.Update();
		for (int i = 0; i < cruiser.projectiles.size(); i++)
		{
			if (!cruiser.projectiles[i].shot)
			{
				cruiser.projectiles.erase(cruiser.projectiles.begin() + i);
				i--;
			}
		}

		for (auto& ep : enemiesProjectiles) ep.Update(); // Uruchomienie metody Update() dla pocisków wrogów
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
			std::uniform_int_distribution<> dist(10, 20);
			ufoCooldown = dist(rng);
		}
		EnemyFire();
		UpdateEnemies();
		//OutOfScreen();
		ufo.Update();
		CollisionsCheck();

		if (enemies.empty()) {
			enemies = InitEnemies();
			waveCounter++;
			SetEnemiesSpeed(GetEnemiesSpeed() + 1); // zwiekszenie poziomu trudnosci przy kolejnych falach
			if (waveCounter != 0 && waveCounter % 2 == 0) lives++;
		}
	}
	else {
		if (IsKeyPressed(KEY_ENTER)) {
			ClearObjects();
			InitGame();
		}
	}
}

void Game::Inputs()
{
	if (IsKeyPressed(KEY_P)) TogglePause();
	if (isGameRunning&& !isPaused) {
		if (IsKeyDown(KEY_A)) cruiser.MoveL();
		if (IsKeyDown(KEY_D)) cruiser.MoveR();
		//if (IsKeyPressed(KEY_SPACE)) spaceship.Fire(); - zamiast tego dodalem delay do strzalow
		if (IsKeyDown(KEY_SPACE)) cruiser.Fire();
	}
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

size_t Game::GetSizeOfEnemies()
{
	return size_t(enemies.size());
}

void Game::SetLives(int lives)
{
	this->lives = lives;
}

int Game::GetLives()
{
	return lives;
}

void Game::TogglePause()
{
	isPaused = !isPaused;
}

void Game::DeathScreen()
{
	SaveScore(playerScore); // Save the current score
	int highScore = GetHighScore(); // Get the high score
	isGameRunning = false;
	// tutaj bedzie ekran smierci
	std::cout << "Game Over! Your score: " << playerScore << std::endl;
	std::cout << "High Score: " << highScore << std::endl;
}

void Game::ClearObjects()
{
	cruiser.ResetPlayer();
	enemies.clear();
	enemiesProjectiles.clear();
	asteroids.clear();
}

void Game::InitGame()
{
	asteroids = InitAsteroids();
	enemies = InitEnemies();
	enemiesCourse = 2;
	lives = 3;
	lastEnemyFire = 0.0;
	lastUfo = 0.0;
	playerScore = 0;
	waveCounter = 0;
	std::uniform_int_distribution<> dist(10, 20);
	ufoCooldown = dist(rng);
	isGameRunning = true;
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
	size_t asteroidWidth = Asteroid::mesh[0].size() * 4;
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
		if (!isImmune && CheckCollisionRecs(ep.GetHitbox(), cruiser.GetHitbox())) // Kolizje strzalow wrogow z graczem
		{
			ep.shot = false;
			lives--;
			isImmune = true;
			immunityTime = GetTime();
			std::cout << "kolizja ze strzalem wroga" << std::endl;
			if (lives == 0) DeathScreen();
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
		if (CheckCollisionRecs(e.GetHitbox(), cruiser.GetHitbox())) // Kolizje przeciwnikow z graczem
		{
			DeathScreen();
			std::cout << "bezposrednia kolizja z wrogiem" << std::endl;
		}
	}
	// KOLIZJE GRACZA Z PRZECIWNIKAMI
	for (auto& cp : cruiser.projectiles)
	{
		auto i = enemies.begin();
		while (i != enemies.end())
		{
			if (CheckCollisionRecs(cp.GetHitbox(), i->GetHitbox()))
			{
				if (i->GetType() == 1) playerScore += 10;
				if (i->GetType() == 2) playerScore += 20;
				if (i->GetType() == 3) playerScore += 30;
				DrawTextureV(explosion, {cp.GetHitbox().x-15,cp.GetHitbox().y}, WHITE);
				i = enemies.erase(i);
				//PlaySound(sound);
				cp.shot = false;
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
				if (CheckCollisionRecs(cp.GetHitbox(), i->GetHitbox()))
				{
					i = a.decays.erase(i);
					cp.shot = false;
				}
				else
				{
					++i;
				}
			}
		}
		if (CheckCollisionRecs(ufo.GetHitbox(), cp.GetHitbox()))
		{
			DrawTextureV(explosion, { cp.GetHitbox().x - 15,cp.GetHitbox().y }, WHITE);
			ufo.spawned = false;
			//PlaySound(sound);
			cp.shot = false;
			playerScore += 100;
		}
	}

}

void Game::EnemyFire()
{
	if (GetSizeOfEnemies() > 0) {
		std::uniform_int_distribution<int> dist(0, GetSizeOfEnemies() - 1);
		double currentTime = GetTime();
		if (currentTime - lastEnemyFire >= enemyFireCooldown && enemies.size() > 0) {
			int random = dist(rng);
			Enemy& enemy = enemies[random];
			enemiesProjectiles.push_back(Projectile({ enemy.GetPosition().x + enemy.textures[enemy.GetType() - 1].width / 2 - 3, enemy.GetPosition().y + enemy.textures[enemy.GetType() - 1].height }, 5, false));
			lastEnemyFire = currentTime;
		}
	}
}

void Game::UpdateEnemies()
{
	for (auto& e : enemies)
	{
		if (e.GetPosition().x + e.textures[e.GetType() - 1].width > GetScreenWidth())
		{
			enemiesCourse = -GetEnemiesSpeed(); // Zmiana kierunku
			for (auto& e : enemies) e.position.y += GetEnemiesDownSpeed();
		}
		if (e.GetPosition().x < 0) {
			enemiesCourse = GetEnemiesSpeed();
			for (auto& e : enemies) e.position.y += GetEnemiesDownSpeed();
		}

		e.Update(enemiesCourse);
	}
}
