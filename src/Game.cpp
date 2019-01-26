#include "Game.h"
#include <vector>
//#include "Map.h"

using namespace std;

//Map *map = new Map();

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
        //create map
        //Map *map = new Map();
        //map->Init();
        //map->DrawMap(renderer);

        //Is Running
        is_running = true;
    }
    else {

        //Is Running
        is_running = false;
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
    if (SDL_GetTicks() / 50 > fps) {
    fps++;

    if (shot->Fired()) {
        shot->Update();
        shot->ChangeSpeed(0, -30);
    }

    //Delete Exteras
    if(shot->des_rec.y < 0)
        shot->fired = 0;
    }

    //lvl update
    if ((score / 600) > lvl) {

        map->Update(score, lvl % 2);

        lvl++;
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

    //map->DrawMap(renderer);

    //Present Renderer
    SDL_RenderPresent(renderer);
}

//Handel Events
void Game::HandelEvents() {

    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        is_running = false;
    }

    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
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
