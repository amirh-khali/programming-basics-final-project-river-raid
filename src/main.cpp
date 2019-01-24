#include "main.h"
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
