// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"
#include "game.h"


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
        DrawLineEx({ 0,50 }, { screenWidth,50 }, 5, BROWN);
		DrawLineEx({ 0,screenHeight }, { screenWidth,screenHeight }, 5, BROWN);
        if (game.isGameRunning)
            DrawTextEx(spaceFont, "WAVE CLEARED:1", { screenWidth - 350,screenHeight + 5 }, 34, 2, BROWN);
        else {
            DrawTextEx(spaceFont, "GAME OVER", { screenWidth / 4 + 20,screenHeight / 2 + 50 }, 100, 2, RED);
            DrawTextEx(spaceFont, "PRESS ENTER TO RESTART", { screenWidth / 4 + 20,screenHeight / 2 + 150 }, 50, 2, RED);
        }
        for (int i{ 0 }; i < game.GetLives();i++) {
            DrawTextureEx(heartSymbol, {50.0f + (50.0f * i), static_cast<float>(screenHeight) + 4.0f}, 0.0f, 4.0f, WHITE);
        }
        game.Draw();

		
        //DrawTextureEx(txture, { 100,100 }, 0, 4, WHITE);
		



        EndDrawing();
    }
	CloseAudioDevice();
    CloseWindow();
    return 0;
}
