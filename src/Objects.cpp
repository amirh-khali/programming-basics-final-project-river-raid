#include "Objects.h"

//Constructor
Objects::Objects() {}

//Initialize
void Objects::Init(int x_pos, int y_pos) {

    //Set Object Size
    des_rec.h = 32;
    des_rec.w = 32;

    //Set Object location
    des_rec.x = x_pos;
    des_rec.y = y_pos;

    //Load Texture
    //image_path = path;

}
