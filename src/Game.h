#ifndef GAME_DEF_
#define GAME_DEF_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstring>
#include "Objects.h"

class Objects;

class Game {
    public:
        //Constructor
        Game();

        //Initialize
        void Init();

        //Update
        void Update();

        //Render
        void Render();

        //Handel Events
        void HandelEvents();

        //Position Of Running
        bool IsRunning();

    private:
        SDL_Renderer *renderer = NULL;
        SDL_Window *window = NULL;
        bool is_running = false;
        Objects *fighter_jet = nullptr;
};

#endif //GAME_DEF_
