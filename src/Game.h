#ifndef GAME_DEF_
#define GAME_DEF_

#include "main.h"
#include "FighterJet.h"
#include "Shot.h"

using namespace std;

class FighterJet;

class Shot;

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
        vector<Shot *> shots;
};

#endif //GAME_DEF_
