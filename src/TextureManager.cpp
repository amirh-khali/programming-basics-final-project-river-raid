#include "TextureManager.h"


SDL_Texture* TextureManager::Load_tex(const char* texture, SDL_Renderer* ren){
    SDL_Surface* temp_surface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTxtureFromSurface(ren, tempsurface);
    SDL_FreeSurface(temp_surface)
    return tex;
}