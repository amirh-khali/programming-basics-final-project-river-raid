#ifndef GAME_DEF_
#define GAME_DEF_
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
class Game {
private:
    bool is_running;
    
public:
    Game() {

    }
    void init(const char *title, int x_pos, int y_pos, int width, int height, bool full_screen);
    void update();
    void render();
    void handelEvents();
    void clean();

    bool running();
};
#endif //GAME_DEF_
