#ifndef SHOT_DEF_
#define SHOT_DEF_

#include "main.h"
#include "Objects.h"

class Objects;

class Shot : public Objects {
    public:
        bool Fired();

        bool fired = 0;
    private:
    //y 10 22
    //x 14 18
};

#endif //SHOT_DEF_
