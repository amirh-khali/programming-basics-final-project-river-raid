#ifndef OBJECTS_DEF_
#define OBJECTS_DEF_

#include "main.h"

class Objects {
    public:

        //Constructor
        Objects();

        //Initialize
        void Init(int x_pos = 0, int y_pos = 0);

        //Change Speed
        void ChangeSpeed(int new_vx, int new_vy);

        //Update
        void Update();

        //Object Location && Size
        SDL_Rect des_rec;
    protected:

        //Object Image path
        //std::string image_path;
        //SDL_Surface *surface = NULL;

        //speed
        int vx = 0, vy = 0; // + ^ >
};
#endif //OBJECTS_DEF_
