#include "Game.h"

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
        fighter_jet = new Objects();
        fighter_jet->Init(288, 240);

        //Is Running
        is_running = true;
    }
    else {

        //Is Running
        is_running = false;
    }
}

//Render
void Game::Render() {

    //Clear Renderer
    SDL_RenderClear(renderer);



    // //Renderer Things
    // SDL_Surface *surface = IMG_Load( "fighter_jet.png" );
    //
    // //GetError
    // // if (surface == NULL) {
    // //     fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    // // }
    //
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);
    //
    // //des_rec
    // SDL_Rect des_rec;
    // des_rec.h = 32;
    // des_rec.w = 32;
    // des_rec.x = 288;
    // des_rec.y = 240;
    //
    // //Copy To Renderer
    // SDL_RenderCopy(renderer, texture, NULL, &des_rec);


    fighter_jet->Render(renderer);


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
}

//Position Of Running
bool Game::IsRunning() {
    return is_running;
}
