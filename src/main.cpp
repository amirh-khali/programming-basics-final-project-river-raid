#include "main.h"
#include "Game.h"
//class Game;

using namespace std;

Game *main_game = nullptr;

void AddScoreToFile(int score) {
    ofstream fout("Resource/highScore/file.txt", ios::out);
    if (main_game->high_score < score) {
        fout << score;
    } else {
        fout << main_game->high_score;
    }
    fout << endl;
    fout.close();
}

int main () {
    srand(time(NULL));
    ifstream fin("Resource/highScore/file.txt");

    main_game = new Game();
    main_game->Init();

    fin >> main_game->high_score;
    fin.close();

    while (main_game->IsRunning()) {

        //cout << SDL_GetTicks() << '\n';

        main_game->MakeEnemies();

        main_game->HandelEvents();

        main_game->Update();

        main_game->Render();


    }
    AddScoreToFile((int)main_game->score / 10);
}
