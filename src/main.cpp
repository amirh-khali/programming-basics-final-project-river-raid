#include "main.h"
#include "Game.h"
//class Game;

using namespace std;

Game *main_game = nullptr;

int hs;

void GameOver() {
    SDL_Renderer *renderer = NULL;

    SDL_Window *window = NULL;

    window = SDL_CreateWindow("Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);

    SDL_Surface *surface = IMG_Load( "Resource/game_over_by_nukechaser24_d8nb2aa-fullview.png" );

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect des_rec = {0, 0, 640, 480};

    SDL_RenderCopy(renderer, texture, NULL, &des_rec);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture( texture );

    SDL_Color textColor = { 255, 255, 0, 255 };

    std::stringstream timeText;
    timeText.str( "" );
    timeText << "High Score     " << hs << "     Score     " << main_game->score / 10;

    TTF_Font *gFont = TTF_OpenFont( "Resource/Font/ATARCC__.TTF", 28 );

    //Load Surface
    surface = TTF_RenderText_Solid( gFont, timeText.str().c_str(), textColor);

    //Create Texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);

    SDL_Rect des_rec1;
    des_rec1.x = 30;
    des_rec1.y = 30;
    des_rec1.w = 400;
    des_rec1.h = 64;

    //Copy To Renderer
    //SDL_RenderCopy(renderer, texture, NULL, &des_rec);
    SDL_RenderCopyEx( renderer, texture, NULL, &des_rec1, 0.0, NULL, SDL_FLIP_NONE );

    //Free Surface & Texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture( texture );

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
}

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

    fin >> hs;
    fin.close();

    main_game->high_score = hs;

    while (main_game->IsRunning()) {

        //cout << SDL_GetTicks() << '\n';

        main_game->MakeEnemies();

        main_game->HandelEvents();

        main_game->Update();

        main_game->Render();


    }

    if (main_game->high_score > hs)
        hs = main_game->high_score;

    GameOver();

    AddScoreToFile((int)main_game->score / 10);
}
