#ifndef GAME_DEF_
#define GAME_DEF_

#include "main.h"
#include "FighterJet.h"
#include "Shot.h"
#include "Map.h"

using namespace std;

class FighterJet;

class Shot;

class Map;

class Game {
    public:
        //Constructor
        Game();
        ~Game();

        void Init();
        void Update();
        void Render();
        void HandelEvents();

        bool IsRunning();

    private:
        //Main Renderer
        SDL_Renderer *renderer = NULL;

        //Main Window
        SDL_Window *window = NULL;

        //Running Pos
        bool is_running = false;

        FighterJet *fighter_jet = nullptr;
        Shot *shot = nullptr;
        //Map *map = nullptr;
        int fps = 0;
};

#endif //GAME_DEF_
