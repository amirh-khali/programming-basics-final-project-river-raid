#ifndef OBJECTS_DEF_
#define OBJECTS_DEF_

#include "main.h"

class Objects {
    public:

        Objects();
        ~Objects();

        void Init(int x_pos = 0, int y_pos = 0, int h = 32, int w = 32);
        void Render(SDL_Renderer *renderer, const char *path);
        void ChangeSpeed(int new_vx, int new_vy);
        void Update();

        //Object Location && Siz
        SDL_Rect des_rec;

        //speed
        int vx = 0, vy = 0; // + ^ >

    protected:
};
#endif //OBJECTS_DEF_
