#include "Map.h"

void Map::Init() {

}

void Map::Update(int start_break, bool bway) {

    start_wall_break = start_break;
    finish_wall_break = start_break + 128;

    Broadway = bway;
}

void Map::Render(SDL_Renderer *renderer, Uint32 score) {

    //Change Color
    SDL_SetRenderDrawColor(renderer, 40, 111, 15, SDL_ALPHA_OPAQUE);

    //Make Lines
    for (int i = 0; i < 480; ++i) {

        //cout << score << ' ' << start_wall_break << ' ' << i << ' ' << i - (int)score + start_wall_break <<  ' ' << finish_wall_break << '\n';
        if (!Broadway) {
            if ((int)score - i > finish_wall_break) {
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall + 128), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall + 128), i, 640, i);
            }
            else if ((int)score - i > start_wall_break) {
                //cout << ".\n";
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall + (int)score - i - start_wall_break), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall + (int)score - i - start_wall_break), i, 640, i);
            }
            else {
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall), i, 640, i);
            }
        }
        else {
            if ((int)score - i > finish_wall_break) {
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall), i, 640, i);
            }
            else if ((int)score - i > start_wall_break) {
                //cout << ".\n";
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall + 128 - (int)score + i + start_wall_break), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall + 128 - (int)score + i + start_wall_break), i, 640, i);
            }
            else {
                SDL_RenderDrawLine(renderer, 0, i, (size_of_wall + 128), i);
                SDL_RenderDrawLine(renderer, 640 - (size_of_wall + 128), i, 640, i);
            }
        }
    }
}
