#ifndef ENEMIES_DEF_
#define ENEMIES_DEF_

#include "main.h"
#include "Objects.h"
#include "Shot.h"

class Objects;

class Shot;

class Enemies : public Objects {
    public:

        bool OnScreen();

        void Calibrate();

        void ShotUpdate();

        void ShotInit();

        bool on_screen = 0;

        int type;
        // 0 barrier, 1 helicopter, 2 jet, 3 tanker

        int left, right, up, down;

        Shot *shot = nullptr;

        bool explos = 0;

        int explos_time = 0;

    private:
        //tanker y 22 40
        //tanker x 0 64
};

#endif //ENEMIES_DEF_
