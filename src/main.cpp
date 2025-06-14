#include "raylib.h"
#include "globals.h"
#include "game.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Game* game = nullptr;

void mainLoop()
{
    float dt = GetFrameTime();
    game->Update(dt);
    game->Draw(dt);
}

int main()
{
    InitWindow(gameScreenWidth, gameScreenHeight, "Minesweeper");
    InitAudioDevice();  // Initialize audio device
#ifndef EMSCRIPTEN_BUILD
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    ToggleBorderlessWindowed();
#endif
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    
    game = new Game(gameScreenWidth, gameScreenHeight);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    while (!WindowShouldClose() && !exitWindowRequested)
    {
        mainLoop();
    }
    delete game;
    CloseAudioDevice();  // Close audio device
    CloseWindow();
#endif

    return 0;
}