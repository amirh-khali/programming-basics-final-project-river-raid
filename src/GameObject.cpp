#include "GameObject.h"

GameObject::GameObject(const char* texture, SDL_Renderer* ren){
    renderer = ren;
    obj_texture = TextureManager::Load_tex(texture, ren);

}

void GameObject::Update(){
    xpos = 0;
    ypos = 0;

    //temporary(size and positions will be changed)
    src_rec.h = 32;
    src_rec.w = 32;
    src_rec.x = 0;
    src_rec.y = 0;

    des_rec.h = 64;
    des_rec.w = 64;
    src_rec.x = xpos;
    src_rec.y = ypos;

}

void GameObject::Render(){
    SDL_RenderCopy(renderer, obj_texture, &src_rec, &des_rec);
}