#include "explosion.h"
#include <raylib.h>

// Initialize static members
Texture2D Explosion::textures[7];
bool Explosion::texturesLoaded = false;
Sound Explosion::sound;
bool Explosion::soundLoaded = false;

Explosion::Explosion(Vector2 position, bool isUFO) : position(position), isUFO(isUFO), frameCounter(0), frameSpeed(0.1f), currentFrame(0), isFinished(false) {
    if (!texturesLoaded) {
        // Load textures
        
        textures[0] = LoadTexture("explosion1.png");
		textures[1] = LoadTexture("explosion2.png");
		textures[2] = LoadTexture("explosion3.png");
		textures[3] = LoadTexture("explosion4.png");
		textures[4] = LoadTexture("explosion5.png");
		textures[5] = LoadTexture("explosion6.png");
		textures[6] = LoadTexture("explosion7.png");
        
        texturesLoaded = true;
    }
    if (!soundLoaded) {
        sound = LoadSound("explosion.wav");
        soundLoaded = true;
    }
    PlaySound(sound);
}

Explosion::~Explosion() {
    // Destructor
}

void Explosion::Update() {
    frameCounter += GetFrameTime();
    if (frameCounter >= frameSpeed) {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame >= 7) {
            isFinished = true;
        }
    }
}

void Explosion::Draw() {
    if (!isFinished) {
        DrawTexture(textures[currentFrame], position.x, position.y, WHITE);
    }
}

void Explosion::UnloadResources() {
    if (texturesLoaded) {
        for (int i = 0; i < 7; i++) {
            UnloadTexture(textures[i]);
        }
        texturesLoaded = false;
    }
    if (soundLoaded) {
        UnloadSound(sound);
        soundLoaded = false;
    }
}
