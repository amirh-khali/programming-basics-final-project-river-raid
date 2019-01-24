#ifndef GAME_DEF_
#define GAME_DEF_

#include "main.h"
#include "FighterJet.h"

class FighterJet;

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
        FighterJet *fighter_jet = nullptr;
};

#endif //GAME_DEF_
