#ifndef MAP_DEF_
#define MAP_DEF_

#include "main.h"

class Map(){

    public:
        Map();
        ~Map();
        
        void Init();
        void Draw_map();

    private:
        SDL_Rec src_rec, des_rec;

        SDL_Texture *ground; 
        int map[20][30];
};
#endif