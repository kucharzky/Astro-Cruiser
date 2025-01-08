// Astro Cruiser.cpp : Defines the entry point for the application.
//

#include "Astro Cruiser.h"


int main()
{
    // Paleta kolorów
    const Color palePurple = { 255, 228, 250, 255 };
    const Color lavenderPink = { 255, 196, 235, 255 };
    const Color mistyRose = { 241, 222, 220, 255 };
    const Color pearl = { 225, 218, 189, 255 };
    const Color olivine = { 171, 199, 152, 255 };
    // Rozmiar okna gry
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 900;



    InitWindow(screenWidth, screenHeight, "Astro Cruiser : rev 0.1");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(pearl);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
