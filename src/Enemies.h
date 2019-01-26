#ifndef ENEMIES_DEF_
#define ENEMIES_DEF_

#include "main.h"
#include "Objects.h"

class Objects;

class Enemies : public Objects {
    public:

        bool OnScreen();

        bool on_screen = 0;

        int type;
        // 0 barrier, 1 helicopter, 2 jet, 3 tanker 

    private:
};

#endif //ENEMIES_DEF_
