#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstring>
#include "Game.h"
//class Game;

Game *main_game = nullptr;

int main () {
    main_game = new Game();
    main_game->Init();
    main_game->Render();
    while (main_game->IsRunning()) {
        main_game->HandelEvents();
    }
}
