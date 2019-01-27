#ifndef GAME_DEF_
#define GAME_DEF_

#include "main.h"
#include "FighterJet.h"
#include "Shot.h"
#include "Enemies.h"
#include "Map.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>


using namespace std;

class FighterJet;

class Shot;

class Enemies;

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
        void MakeEnemies();

        bool IsRunning();

    private:
        //Main Renderer
        SDL_Renderer *renderer = NULL;

        //Main Window
        SDL_Window *window = NULL;

        //Running Pos
        bool is_running = false;

        Uint32 score = 0;

        FighterJet *fighter_jet = nullptr;
        Shot *shot = nullptr;
        Map *map = nullptr;

        //Enemies
        Enemies *enemies[5];
        int enemies_num = 0, last_enemy = 0;

        Uint32 fps = 0;

        int lvl = 0;

        TTF_Font *gFont = NULL;
};

#endif //GAME_DEF_
