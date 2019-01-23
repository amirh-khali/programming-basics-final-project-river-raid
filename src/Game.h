#ifndef GAME_DEF_
#define GAME_DEF_
#include "main.h"

class Game {
    private:
        bool is_running;
        int size_of_wall = 160;
        SDL_Window *window;
        SDL_Renderer *renderer;
    public:
        Game();
        ~Game();

        void Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen);
        void Update();
        void Background();
        void Render();
        void HandelEvents();
        void Clean();

        bool Running();
};
#endif //GAME_DEF_
