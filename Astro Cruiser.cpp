// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"
#include "game.h"
#include <string>

// stany gry
// do przechodzenia miedzy menu glownym, rozgrywka a creditsami
enum GameState {
    MAIN_MENU,GAMEPLAY,CREDITS
};
std::vector<int> GetTopScores(int count) {
    std::vector<int> scores = LoadScores();
    std::sort(scores.rbegin(), scores.rend()); // sortowanie w od najwyzszego
    if (scores.size() > count) {
        scores.resize(count); // zatrzymuje tylko najlepsze wyniki
    }
    return scores;
}
int main()
{

    int offset = 50;
    // inicjalizacja okienka o wielkosci 1280 x 720 + 50
    InitWindow(screenWidth, screenHeight+offset, "Astro Cruiser : rev 0.4");
    Font spaceFont = LoadFontEx("textures/SpaceMadness.ttf", 64, 0, 0);
    Texture2D heartSymbol = LoadTexture("textures/heart.png");
    Texture2D mainLogo = LoadTexture("textures/mainlogo.png");
    Texture2D menuBackground = LoadTexture("textures/menu_background.png");
    Texture2D gameplayBackground = LoadTexture("textures/gameplay_background.png");
    Button startButton{ "textures/start.png",{500, 420},2 };
    Button exitButton{ "textures/exit.png",{500,640},2 };
    Button creditsButton{ "textures/credits.png",{500,530},2 };
    Button returnButton{ "textures/return.png",{520,550},2 };
    SetTargetFPS(60);
    InitAudioDevice();
    
    Game game;
    GameState gameState = MAIN_MENU;
    std::vector<int> topScores = GetTopScores(10);
    while (!WindowShouldClose())
    {
        Vector2 mousePosition{ GetMousePosition() };
        // sprawdzanie nacisniecia przycisku myszy
        // do sprawdzania nacisniec przyskow w menu glownym
        bool mousePressed{ IsMouseButtonPressed(MOUSE_BUTTON_LEFT) }; 

        switch (gameState) {
        case GAMEPLAY:
            UpdateMusicStream(game.gameplayMusic); // muzyka w trakcie rozgrywki
            game.Inputs();
            game.Update();
            BeginDrawing();
            ClearBackground(BLACK);
            // rysowanie tla
            for (int y = 0; y < screenHeight + offset; y += gameplayBackground.height) {
                for (int x = 0; x < screenWidth; x += gameplayBackground.width) {
                    DrawTexture(gameplayBackground, x, y, WHITE);
                }
            }
            game.Draw();
            DrawTextEx(spaceFont, ("SCORE:" + std::to_string(game.playerScore)).c_str(), { 10,10 }, 34, 2, BROWN);
            DrawLineEx({ 0,50 }, { screenWidth,50 }, 5, BROWN);
            if (game.isGameRunning)
                DrawTextEx(spaceFont, ("WAVE CLEARED:" + std::to_string(game.waveCounter)).c_str(), { screenWidth - 350,10 }, 34, 2, BROWN);
            else {
                DrawRectangle(0, 0, screenWidth, screenHeight + offset, { 0, 0, 0, 200 });
                DrawTextEx(spaceFont, "GAME OVER", { screenWidth / 4 - 80,screenHeight / 4 }, 150, 1, YELLOW);
                DrawTextEx(spaceFont, "PRESS ENTER TO RESTART", { screenWidth / 4 - 30,screenHeight / 2 }, 50, 2, RED);
                DrawTextEx(spaceFont, ("HIGHSCORE:" + std::to_string(GetHighScore())).c_str(), { screenWidth / 4 + 80,screenHeight / 2 + 100 }, 50, 2, RED);
            }
            if (game.isPaused) {
                DrawRectangle(0, 0, screenWidth, screenHeight + offset, { 0, 0, 0, 200 });
                DrawTextEx(spaceFont, "PAUSED", { screenWidth / 4 + 120, screenHeight / 4 }, 100, 2, YELLOW);
                if (returnButton.isPressed(mousePosition, mousePressed))gameState = MAIN_MENU;
                returnButton.Draw();
            }
            for (int i{ 0 }; i < game.GetLives();i++) {
                DrawTextureEx(heartSymbol, { screenWidth / 2 - 78.0f + (50.0f * i), static_cast<float>(screenHeight) + 3.0f }, 0.0f, 4.0f, WHITE);
            }
            EndDrawing();
            break;
        case MAIN_MENU:
            // warunki wcisniecia przysikow w menu glownym
            if (startButton.isPressed(mousePosition, mousePressed)) {
                gameState = GAMEPLAY; // przysik start -> wlaczenie gry
            }
            else if (exitButton.isPressed(mousePosition, mousePressed)) {
                CloseWindow(); // exit -> wyjscie z gry
                return 0;
            }
            else if (creditsButton.isPressed(mousePosition, mousePressed)) {
                gameState = CREDITS; // credits -> przejscie do creditsow
            }
            UpdateMusicStream(game.mainMenuMusic); // muzyka w menu glownym
            BeginDrawing();
            ClearBackground(BLACK);
            // rysowanie tla
            for (int y = 0; y < screenHeight + offset; y += menuBackground.height) {
                for (int x = 0; x < screenWidth; x += menuBackground.width) {
                    DrawTexture(menuBackground, x, y, {255,255,255,80});
                }
            }
            DrawTexture(mainLogo, screenWidth / 2 - mainLogo.width / 2, 50, WHITE);
            // rysowanie przyciskow
            startButton.Draw();
            exitButton.Draw();
            creditsButton.Draw();
            // wyswietalnie top 10
            DrawTextEx(spaceFont, "TOP 10 HIGH SCORES", { 20.0, 420.0f }, 30.0f, 2.0f, YELLOW);
            for (int i = 0; i < topScores.size(); i++) {
                DrawTextEx(spaceFont, ("* "+std::to_string(topScores[i])).c_str(), {80.0, 450.0f + i * 30.0f}, 30.0f, 2.0f, WHITE);
            }
            EndDrawing();
            break;
        case CREDITS:
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(spaceFont, "CREDITS", { screenWidth / 2 - 160, 100 }, 50, 2, YELLOW);
            DrawTextEx(spaceFont, "Game developed by Maciej Kucharski", { 50, 200 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Font ''Space Madness'' by Rose Frye", { 50, 250 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Mental support: Michal Gorka", { 50, 300 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Space Music Pack by Goose Ninja", { 50, 350 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Background: SPACE by SPACE", { 50, 400 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Enemy and ship texture: Space Eaters! Asset Pack by Cluly", { 50, 450 }, 30, 2, WHITE);
            DrawTextEx(spaceFont, "Sound effects and other textures by Maciej Kucharski", { 50, 500 }, 30, 2, WHITE);
            if (returnButton.isPressed(mousePosition, mousePressed))gameState = MAIN_MENU;
            returnButton.Draw();
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) {
                gameState = MAIN_MENU;
            }
            break;
        }
        
    }
    UnloadTexture(mainLogo);
    UnloadTexture(heartSymbol);
    UnloadTexture(menuBackground);
    UnloadTexture(gameplayBackground);
    UnloadFont(spaceFont);
	CloseAudioDevice();
    CloseWindow();
    return 0;
}
