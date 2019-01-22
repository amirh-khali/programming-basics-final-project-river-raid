#ifndef TEXTUREMANAGER_DEF_
#define  TEXTUREMANAGER_DEF_
#include "Game.h"

class TextureManager{

    public:
        static SDL_Texture* Load_tex(const char* filename, SDL_Renderer* ren);
        

}