#include "Shot.h"

void Shot::Render(SDL_Renderer *renderer) {

    //Load Surface
    //std::cout << image_path << '\n';
    SDL_Surface *surface = IMG_Load( "Resource/shot.png" );

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

bool Shot::Fired() {
    return fired;
}
