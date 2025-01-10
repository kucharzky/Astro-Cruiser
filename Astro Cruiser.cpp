// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"
#include "game.h"


int main()
{


    InitWindow(screenWidth, screenHeight, "Astro Cruiser : rev 0.1");
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
		
        //DrawTextureEx(txture, { 100,100 }, 0, 4, WHITE);


        EndDrawing();
    }
	CloseAudioDevice();
    CloseWindow();
    return 0;
}
