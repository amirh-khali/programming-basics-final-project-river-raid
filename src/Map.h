#ifndef MAP_DEF_
#define MAP_DEF_

#include "main.h"

class Map {

    public:
        Map();
        ~Map();

        void Init();

        void DrawMap(SDL_Renderer *renderer);
    private:
        SDL_Rect src_rec, des_rec;
        SDL_Texture *ground = NULL;
        //int map[20][30];
};

#endif //MAP_DEF_
