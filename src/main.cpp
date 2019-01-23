#include "main.h"
#include "Game.h"

Game *main_game = nullptr;

int main () {
    main_game = new Game();
    main_game->Init("River Raid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    while(main_game->Running()) {

        main_game->HandelEvents();
        main_game->Update();

        main_game->Render();
    }
     return 0;
 }
