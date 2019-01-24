#ifndef OBJECTS_DEF_
#define OBJECTS_DEF_

#include "main.h"

class Objects {
    public:

        //Constructor
        Objects();

        //Initialize
        void Init(int x_pos, int y_pos);

        //Update
        void Update();

    protected:

        //Object Image path
        //std::string image_path;
        //SDL_Surface *surface = NULL;

        //Object Location && Size
        SDL_Rect des_rec;
};
#endif //OBJECTS_DEF_
