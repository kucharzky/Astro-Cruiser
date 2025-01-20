// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"
#include "game.h"
#include <string>


int main()
{

    int offset = 50;
    InitWindow(screenWidth, screenHeight+offset, "Astro Cruiser : rev 0.2");
    Font spaceFont = LoadFontEx("textures/SpaceMadness.ttf", 64, 0, 0);
    Texture2D heartSymbol = LoadTexture("textures/heart.png");
    SetTargetFPS(60);
    InitAudioDevice();
    /*Texture2D background = LoadTexture("graphics/mainlogo.png");
    Button startButton{ "graphics/start.png",{500, 400},2 };
    Button exitButton{ "graphics/exit.png",{500,550},2 };*/
    Game game;
    //Texture2D txture = LoadTexture("textures/asteroid.png");

    while (!WindowShouldClose())
    {
        Vector2 mousePosition{ GetMousePosition() };
        bool mousePressed{ IsMouseButtonPressed(MOUSE_BUTTON_LEFT) };
        
		    // Sprawdzanie przycisków
        /*if (startButton.isPressed(mousePosition, mousePressed))
        {
            UnloadTexture(background);
            startButton.~Button();
            exitButton.~Button();
            radius = 20;
        }
        else if (exitButton.isPressed(mousePosition, mousePressed))
        {
            break;
        }
        else
        {
            DrawTexture(background, 0, 0, WHITE);
            startButton.Draw();
            exitButton.Draw();
        }*/
		// Eventy
        game.Inputs();
		game.Update();

        // Rysowanie
        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        DrawTextEx(spaceFont, ("SCORE:" + std::to_string(game.playerScore)).c_str(), { 10,10 }, 34, 2, BROWN);
        DrawLineEx({ 0,50 }, { screenWidth,50 }, 5, BROWN);
        if (game.isGameRunning)
            DrawTextEx(spaceFont, ("WAVE CLEARED:" + std::to_string(game.waveCounter)).c_str(), {screenWidth - 350,10}, 34, 2, BROWN);
        else {
            DrawRectangle(0, 0, screenWidth, screenHeight + offset, { 0, 0, 0, 200 });
            DrawTextEx(spaceFont, "GAME OVER", { screenWidth / 4-80,screenHeight / 4 }, 150, 1, YELLOW);
            DrawTextEx(spaceFont, "PRESS ENTER TO RESTART", { screenWidth / 4-30,screenHeight / 2}, 50, 2, RED);
            DrawTextEx(spaceFont, ("HIGHSCORE:"+std::to_string(GetHighScore())).c_str(), {screenWidth / 4+80,screenHeight / 2 + 100}, 50, 2, RED);
        }
        if (game.isPaused) {
            DrawRectangle(0, 0, screenWidth, screenHeight + offset, { 0, 0, 0, 200 });
            DrawTextEx(spaceFont, "PAUSED", { screenWidth / 2 - 100, screenHeight / 2 }, 50, 2, YELLOW);
        }
        for (int i{ 0 }; i < game.GetLives();i++) {
            DrawTextureEx(heartSymbol, {screenWidth/2 - 78.0f + (50.0f * i), static_cast<float>(screenHeight) + 3.0f}, 0.0f, 4.0f, WHITE);
        }


        //game.Draw();

            //DrawTextureEx(txture, { 100,100 }, 0, 4, WHITE);
        



        EndDrawing();
    }
	CloseAudioDevice();
    CloseWindow();
    return 0;
}
