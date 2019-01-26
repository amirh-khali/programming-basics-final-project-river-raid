#include "Game.h"
#include <vector>


using namespace std;

//Constructor
Game::Game(){}

//Initialize
void Game::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        //Create window
        window = SDL_CreateWindow("River Raid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
        if (window) {
            std::cout << "Window Created!...." << std::endl;
        }

        //Create Renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer Created!...." << std::endl;
            SDL_SetRenderDrawColor(renderer, 34, 44, 141, 255);
        }

        //create fighter_jet
        fighter_jet = new FighterJet();
        fighter_jet->Init(288, 240);

        shot = new Shot();

        map = new Map();

        for (int i = 0; i < 3; ++i) {
            enemies[i] = new Enemies();
        }

        //Is Running
        is_running = true;
    }
    else {

        //Is Running
        is_running = false;
    }
}

//Enemies
void Game::MakeEnemies() {

    bool n_add_enemy;
    n_add_enemy = rand() % 1000;

    if (!n_add_enemy && enemies_num < 3) {

        int type = rand() % 4;
        enemies[last_enemy]->type = 3;

        enemies[last_enemy]->on_screen = 1;

        int wall_size;
        if (score >= map->start_wall_break && score <= map->finish_wall_break) {
            wall_size = 256;
        }
        else {
            wall_size = map->size_of_wall;
        }
        int x_pos = rand() % (640 - 2 * wall_size - 126);
        x_pos += wall_size + 63 ;

        enemies[last_enemy]->ChangeSpeed(0, 3);

        enemies[last_enemy]->Init(x_pos, 0, 64, 64);
        enemies_num++;

        last_enemy++;
        last_enemy %= 3;
    }
}


//Update
void Game::Update() {

    score = SDL_GetTicks() / (10);
    //cout << score << '\n';

    //speed_booster = score / 1000;

    //FighterJet Update
    fighter_jet->Update();

    //Shots Update
    if (SDL_GetTicks() / 30 > fps) {
        fps++;

        if (shot->Fired()) {
            shot->Update();
            shot->ChangeSpeed(0, -20);
        }

        //Delete Exteras
        if(shot->des_rec.y < 0)
            shot->fired = 0;

        for (int i = 0; i < 3; ++i) {
            if (enemies[i]->OnScreen()) {
                int vx, vy;
                vx = enemies[i]->vx;
                vx = enemies[i]->vy;

                enemies[i]->Update();
                enemies[i]->ChangeSpeed(0, 3);
            }

            if (enemies[i]->des_rec.y > 480) {
                    enemies[i]->on_screen = 0;
                    enemies_num--;
            }

            //Kill
            if(shot->Fired()
            && enemies[i]->OnScreen()
            && fighter_jet->des_rec.y > enemies[i]->des_rec.y + 40
            && shot->des_rec.y <= (enemies[i]->des_rec.y + 32)
            && shot->des_rec.x >= enemies[i]->des_rec.x
            && shot->des_rec.x <=  enemies[i]->des_rec.x + 64) {
                enemies[i]->on_screen = 0;
                enemies_num--;
                shot->fired = 0;
            }

            //Crash
            if( enemies[i]->OnScreen()
            && fighter_jet->des_rec.y <= (enemies[i]->des_rec.y + 32)
            && fighter_jet->des_rec.y + 32 >= (enemies[i]->des_rec.y)
            && fighter_jet->des_rec.x + 32 >= enemies[i]->des_rec.x
            && fighter_jet->des_rec.x <=  enemies[i]->des_rec.x + 64){
                cout<<"boom"<<endl;
                is_running = false;
            }
        }
    }
    //lvl update
    if ((score / 600) > lvl) {

        //cout << score << '\n';
        map->Update(score, lvl % 2);

        lvl++;
    }

    if ((int)score - fighter_jet->des_rec.y < map->start_wall_break) {
        if (!map->broadway) {
            if (fighter_jet->des_rec.x + 32 >= 640 - 128 || fighter_jet->des_rec.x <= 128) {
                is_running = false;
                cout << "1\n";
            }
        }
        else {
            if (fighter_jet->des_rec.x + 32 >= 640 - 256 || fighter_jet->des_rec.x <= 256) {
                is_running = false;
                //cout << score << ' ' << fighter_jet->des_rec.y << ' ' << map->start_wall_break << '\n';
                cout << "a::\n";
            }
        }
    }
    else if ((int)score - fighter_jet->des_rec.y < map->finish_wall_break) {
        if (map->broadway) {
            if (fighter_jet->des_rec.x >= 640 - (map->size_of_wall + 128 - (int)score + fighter_jet->des_rec.y + map->start_wall_break) || fighter_jet->des_rec.x <= (map->size_of_wall + 128 - (int)score + fighter_jet->des_rec.y + map->start_wall_break)) {
                is_running = false;
                cout << "b::\n";
            }
        }
        else {
            if (fighter_jet->des_rec.x >= 640 - (map->size_of_wall - 128 + (int)score - fighter_jet->des_rec.y - map->start_wall_break) || fighter_jet->des_rec.x <= (map->size_of_wall - 128 + (int)score - fighter_jet->des_rec.y - map->start_wall_break)) {
                is_running = false;
                cout << "c::\n";
            }
        }
    }
    else {
        if (!map->broadway) {
            if (fighter_jet->des_rec.x + 32 >= 640 - 256 || fighter_jet->des_rec.x <= 256) {
                is_running = false;
                cout << "3\n";
            }
        }
        else {
            if (fighter_jet->des_rec.x + 32 >= 640 - 128 || fighter_jet->des_rec.x <= 128) {
                is_running = false;
                cout << "4\n";
            }
        }
    }
}



//Render
void Game::Render() {

    //River
    SDL_SetRenderDrawColor(renderer, 34, 44, 141, SDL_ALPHA_OPAQUE);

    //Clear Renderer
    SDL_RenderClear(renderer);

    //Renderer Stuffs

    //Map Render
    map->Render(renderer, score);

    //Render FighterJet
    fighter_jet->Render(renderer, "Resource/fighter_jet.png" );

    //Render Shots
    if (shot->Fired())
        shot->Render(renderer, "Resource/shot.png");

    for (int i = 0; i < 3; ++i) {
        if (enemies[i]->OnScreen()) {
            enemies[i]->Render(renderer, "Resource/tanker.png");
            //cout << i << ' ' << enemies[i]->des_rec.x << ' ' << enemies[i]->des_rec.y << '\n';
        }
    }

    //Present Renderer
    SDL_RenderPresent(renderer);
}

//Handel Events
void Game::HandelEvents() {

    SDL_Event event;
    SDL_PollEvent(&event);


    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT ) {
        fighter_jet->ChangeSpeed( 10, 0);
    }

    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
        fighter_jet->ChangeSpeed( -10, 0);
    }

    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z && !shot->Fired()) {

        //Fired
        shot->fired = true;

        //located
        shot->Init(fighter_jet->des_rec.x, fighter_jet->des_rec.y);

        //Change Shot speed
        shot->ChangeSpeed(0, -30);
    }
}

//Position Of Running
bool Game::IsRunning() {
    return is_running;
}
