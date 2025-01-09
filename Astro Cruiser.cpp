// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"
#include "button.h"

int main()
{
    // Początkowa pozycja
    int ballPosX{ screenWidth/2};
    int ballPosY{ screenHeight/2 };
    int radius{ 0 };
    // Paleta kolorów
    /*const Color palePurple = { 255, 228, 250, 255 };
    const Color lavenderPink = { 255, 196, 235, 255 };
    const Color mistyRose = { 241, 222, 220, 255 };
    const Color pearl = { 225, 218, 189, 255 };
    const Color olivine = { 171, 199, 152, 255 };*/

    InitWindow(screenWidth, screenHeight, "Astro Cruiser : rev 0.1");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("graphics/mainlogo.png");
    Button startButton{ "graphics/start.png",{500, 400},2 };
    Button exitButton{ "graphics/exit.png",{500,550},2 };
    //Pętla gry
    while (!WindowShouldClose())
    {
        Vector2 mousePosition{ GetMousePosition() };
        bool mousePressed{ IsMouseButtonPressed(MOUSE_BUTTON_LEFT) };
        // Eventy
        if (IsKeyDown(KEY_D)) ballPosX += 3;
        else if (IsKeyDown(KEY_A)) ballPosX -= 3;
        if (IsKeyDown(KEY_W)) ballPosY -= 3;
        else if (IsKeyDown(KEY_S))ballPosY += 3;
        if (startButton.isPressed(mousePosition, mousePressed))
        {
            UnloadTexture(background);
            startButton.~Button();
            exitButton.~Button();
            radius = 20;
        }
        else if (exitButton.isPressed(mousePosition, mousePressed))
        {
            CloseWindow();
            return 0;
        }
        else
        {
            DrawTexture(background, 0, 0, WHITE);
            startButton.Draw();
            exitButton.Draw();
        }
        // Zmiany pozycji
        
        // Rysowanie
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(ballPosX, ballPosY, radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
