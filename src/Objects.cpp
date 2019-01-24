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

void Objects::Render(SDL_Renderer *renderer) {

    //Load Surface
    //std::cout << image_path << '\n';
    SDL_Surface *surface = IMG_Load( "Resource/fighter_jet.png" );

    //GetError
    if (surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    //Create Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Free surface
    SDL_FreeSurface(surface);

    //Copy To Renderer
    SDL_RenderCopy(renderer, texture, NULL, &des_rec);

}
