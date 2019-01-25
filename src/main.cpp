#include "main.h"
#include "Game.h"
//class Game;

using namespace std;

Game *main_game = nullptr;

int main () {
    main_game = new Game();
    main_game->Init();

    while (main_game->IsRunning()) {

        //cout << SDL_GetTicks() << '\n';

        main_game->HandelEvents();

        main_game->Update();

        main_game->Render();


    }
}
