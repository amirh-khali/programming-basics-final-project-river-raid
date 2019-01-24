#include "main.h"
#include "Game.h"
//class Game;

Game *main_game = nullptr;

int main () {
    main_game = new Game();
    main_game->Init();
    while (main_game->IsRunning()) {
        main_game->HandelEvents();
        
        main_game->Update();
        main_game->Render();
    }
}
