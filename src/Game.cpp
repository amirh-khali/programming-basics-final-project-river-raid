#include "Game.h"

Game::Game() {}
Game::~Game() {}

void Game::Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int flag = 0;

    if (fullscreen) {
        flag = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialised!...." << std::endl;

        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flag);
        if (window) {
            std::cout << "Window Created!...." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 34, 44, 141, SDL_ALPHA_OPAQUE);
            std::cout << "Renderer Created!...." << std::endl;
        }
        is_running = true;
    }
    else {
        is_running = false;
    }
}

void Game::Update() {

}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 34, 44, 141, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    for (int i = 0; i < 160; ++i) {
        SDL_SetRenderDrawColor(renderer, 40, 111, 15, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, i, 0, i, 480);
        SDL_SetRenderDrawColor(renderer, 40, 111, 15, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 640 - i, 0, 640 - i, 480);
    }
    SDL_RenderPresent(renderer);
}


void Game::HandelEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    //std::cout << is_running << std::endl;

    if (event.type == SDL_QUIT) {
        is_running = false;
    }
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!..." << std::endl;
}

bool Game::Running() {
    return is_running;
}
