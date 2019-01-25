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

}

void Objects::Render(SDL_Renderer *renderer, const char *path) {
    //Load Surface
    SDL_Surface *surface = IMG_Load( path );

    //GetError
    if (surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    //Create Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Copy To Renderer
    SDL_RenderCopy(renderer, texture, NULL, &des_rec);

    //Free Surface & Texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture( texture );
}

void Objects::ChangeSpeed(int new_vx, int new_vy) {
    vx = new_vx;
    vy = new_vy;
}

void Objects::Update() {
    des_rec.x += vx;
    des_rec.y += vy;
    vx = 0;
    vy = 0;
}
