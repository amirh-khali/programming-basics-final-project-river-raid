#ifndef SHOT_DEF_
#define SHOT_DEF_

#include "main.h"
#include "Objects.h"

class Objects;

class Shot : public Objects {
    public:

        //Render
        void Render(SDL_Renderer *renderer);

        //Fired
        bool Fired();

        bool fired = 0;
    private:
};

#endif //SHOT_DEF_
