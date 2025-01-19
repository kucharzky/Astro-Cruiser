#pragma once
#include "raylib.h"

class Explosion
{
public:
    Explosion(Vector2 position, bool isUFO);
    ~Explosion();
    void Update();
    void Draw();
    bool isFinished; // Flaga informujaca o zakonczeniu animacji
    static void UnloadResources();
private:
    static Texture2D textures[7]; // Tablica tekstur dla animacji
    static bool texturesLoaded;
    static Sound sound; // Dzwiek eksplozji
    static bool soundLoaded;
    Vector2 position;
    float frameCounter;
    float frameSpeed; // Szybkosc animacji
    int currentFrame;
    bool isUFO;
};