#pragma once
#include "player.h"
#include "asteroid.h"
#include "enemy.h"
#include "ufo.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
/// <>
/// SaveScore() - funkcja odpowiadajaca za zapis wyniku uzyskanego przez gracza do pliku, score to wynik zwracany przez gre
/// LoadScore - wpisuje do wektora wyniki z pliku zapisowego
/// GetHighscore - funkcja sortujaca wyniki z pliku zapisowego - zwraca od najwyzszego do najmniejszego wyniku
/// 
/// Klasa Game - odpowiada za glowny ruch w grze - sklada sie z praktycznie wszystkich klas w calym projekcie
/// Draw() - rysowanie wszelkich podzaleznosci klas dolaczonych do tej
/// Update() - uzywana w glownej petli gry - sprawdzanie czy gra sie rozpoczela, czy nie zostala zapauzowana,
/// sprawdzanie wektorow pociskow, pojawianie sie przeciwkow oraz ufo, sprawdzanie czy wystapily kolizje,
/// ponowna inizjalizacja gdy pokonamy wszystkich wrogow
/// Inputs() - sprawdzanie czy dane przyciski zostaly wcisniete - wywoluja funkcje gdy tak sie stanie
/// TogglePause() - inicjalizuje pauze w grze, przeciwnicy przestaja sie ruszac, zadne inputy nie dzialaja
/// DeathScreen() - pokazuje ekran koncowy przy utracie zyc, nastepuje mozliwosc restartu
/// ClearObjects() - czysczenie tekstur i muzyki
/// InitGame() - wpisanie wartosci podstawowych uzywanych w funkcjach szczegolnie pomocne przy restarcie oraz wyczyszczeniu
/// przeciwnikow
/// CollionsCheck() - sprawdzanie kolizji miedzy prostkatami danych obiektow - rozwazane sa kolizje pociskow gracza z przeciwnikami,
/// ufo, asteroidami, oraz kolizje pociskow wroga z graczem i asteroidami, oraz bezposrednie kolizje wroga z graczem
/// operowane tu sa zycia i tracimy zycia za dane kolizje z graczem
/// </>

void SaveScore(int score);
std::vector<int> LoadScores();
int GetHighScore();

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void Inputs();
	void SetEnemiesSpeed(int speed);
	int GetEnemiesSpeed();
	int GetEnemiesDownSpeed();
	size_t GetSizeOfEnemies();
	void SetLives(int lives);
	int GetLives();
	bool isGameRunning;
	int playerScore;
	int waveCounter;
	bool isPaused;
	void TogglePause();
	Music mainMenuMusic;
	Music gameplayMusic;
private:
	Player cruiser;
	int lives;
	void DeathScreen();
	void ClearObjects();
	void InitGame();
	Texture2D explosion;
	Sound explosionSound;
	std::vector<Asteroid> asteroids;
	std::vector<Asteroid> InitAsteroids();
	std::vector<Enemy> enemies;
	std::vector<Enemy> InitEnemies();
	std::vector<Projectile> enemiesProjectiles;
	void CollisionsCheck();
	void EnemyFire();
	constexpr static float enemyFireCooldown{ 0.5 };
	float lastEnemyFire;
	void UpdateEnemies();
	int enemiesCourse;
	int enemySpeed;
	int enemyDownSpeed;
	UFO ufo;
	float ufoCooldown;
	double lastUfo;
	bool isImmune;
	double immunityTime;
	const double immunityDuration{ 2.0 };
	const float barrierRadius = 40.0f;
	const Color barrierColor = { 175,238,238,128 };
	
};