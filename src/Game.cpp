#include "Game.h"
#include <vector>

using namespace std;

#define pb push_back
#define po pop_back

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
    fighter_jet->Update();
    for (int i = 0; i < shots.size(); ++i) {
        shots[i]->Update();
        shots[i]->ChangeSpeed(0, -10);
    }
    while(shots.front()->des_rec.y <= 0) {
        shots.po();
    }
}



//Render
void Game::Render() {

    //Clear Renderer
    SDL_RenderClear(renderer);


    // //Renderer Stuffs
    fighter_jet->Render(renderer);

    for(int i = 0; i < shots.size(); ++i) {
        shots[i]->Render(renderer);
    }
    //shot = new Shot();
    //shot->Init(288, 140);
    //shot->Render(renderer);


    //Present Renderer
    SDL_RenderPresent(renderer);
}

//Handel Events
void Game::HandelEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    fighter_jet->ChangeSpeed( 10, 0);
                    break;
                case SDLK_LEFT:
                    fighter_jet->ChangeSpeed(-10, 0);
                    break;
                //case SDLK_UP:
                    //fighter_jet->ChangeSpeed(0, -10);
                case SDLK_z:
                    Shot *new_shot = new Shot();
                    new_shot->Init(fighter_jet->des_rec.x, fighter_jet->des_rec.y);
                    new_shot->ChangeSpeed(0, -10);
                    shots.pb(new_shot);
                    break;
            }
            break;
    }
}

//Position Of Running
bool Game::IsRunning() {
    return is_running;
}
