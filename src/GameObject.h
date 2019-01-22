#ifndef GAMEOBJECT_DEF_
#define GAMEOBJECT_DEF_
#include "Game.h"


class GameObject {
    public:
        GameObject(const char* texture, SDL_Renderer* rend)//will be removed after making textuer header file
        ~GameObject();

        void Update();//update function for each obj
        void Render();//render function for each obj

    private:
        //position
        int xpos;
        int ypos;

        SDL_Texture* obj_texture;
        SDL_Rect src_rec, des_rec;//dest_rec will be shown and src_rec is just a temporary template
        SDL_Renderer* renderer;
}
#endif //GAMEOBJECT_DEF_
