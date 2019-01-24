#ifndef FIGHTER_JET_DEF_
#define FIGHTER_JET_DEF_

#include "main.h"
#include "Objects.h"

class Objects;

class FighterJet : public Objects {
    public:

    //Render
    void Render(SDL_Renderer *renderer);

    //Shot
    void Shot();

    protected:

};

#endif //FIGHTER_JET_DEF_
