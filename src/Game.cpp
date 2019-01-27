#include "Game.h"
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>

using namespace std;

SDL_Color textColor = { 0, 0, 0, 255 };

void ScoreRender(SDL_Renderer* renderer, Uint32 score, TTF_Font *gFont, int high_score) {

    std::stringstream timeText;
    timeText.str( "" );
    timeText << "High Score : " << high_score << "              Score : " << score / 10;

    //Load Surface
    SDL_Surface *surface = TTF_RenderText_Solid( gFont, timeText.str().c_str(), textColor);

    //GetError
    if (surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    //Create Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);

    SDL_Rect des_rec;
    des_rec.x = 20;
    des_rec.y = 300;
    des_rec.w = 600;
    des_rec.h = 64;

    //Copy To Renderer
    //SDL_RenderCopy(renderer, texture, NULL, &des_rec);
    SDL_RenderCopyEx( renderer, texture, NULL, &des_rec, 0.0, NULL, SDL_FLIP_NONE );

    //Free Surface & Texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture( texture );
}

//Collision with the wall
bool CollisionWithTheWall (FighterJet *fighter_jet, Map *map, Uint32 score) {
    if ((int)score - fighter_jet->des_rec.y < map->start_wall_break) {
        if (!map->broadway) {
            if (fighter_jet->des_rec.x + 30 >= 640 - 128 || fighter_jet->des_rec.x + 2 <= 128) {
                return true;
            }
        }
        else {
            if (fighter_jet->des_rec.x + 30 >= 640 - 256 || fighter_jet->des_rec.x + 2 <= 256) {
                return true;
            }
        }
    }
    else if ((int)score - fighter_jet->des_rec.y < map->finish_wall_break) {
        if (map->broadway) {
            if (fighter_jet->des_rec.x + 30 >= 640 - (map->size_of_wall + 128 - (int)score + fighter_jet->des_rec.y + map->start_wall_break) || fighter_jet->des_rec.x + 2 <= (map->size_of_wall + 128 - (int)score + fighter_jet->des_rec.y + map->start_wall_break)) {
                return true;
            }
        }
        else {
            if (fighter_jet->des_rec.x + 30 >= 640 - (map->size_of_wall - 128 + (int)score - fighter_jet->des_rec.y - map->start_wall_break) || fighter_jet->des_rec.x + 2 <= (map->size_of_wall - 128 + (int)score - fighter_jet->des_rec.y - map->start_wall_break)) {
                return true;
            }
        }
    }
    else {
        if (!map->broadway) {
            if (fighter_jet->des_rec.x + 30 >= 640 - 256 || fighter_jet->des_rec.x + 2 <= 256) {
                return true;
            }
        }
        else {
            if (fighter_jet->des_rec.x + 30 >= 640 - 128 || fighter_jet->des_rec.x + 2 <= 128) {
                return true;
            }
        }
    }
    return false;
}


//Constructor
Game::Game(){}

//Initialize
void Game::Init() {
    TTF_Init();
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        //Create window
        window = SDL_CreateWindow("River Raid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
        if (window) {
            std::cout << "Window Created!...." << std::endl;
        }

        //Create Renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer Created!...." << std::endl;
            SDL_SetRenderDrawColor(renderer, 34, 44, 141, 255);
        }

        //create fighter_jet
        fighter_jet = new FighterJet();
        fighter_jet->Init(288, 240);

        //create shot
        shot = new Shot();

        //create map
        map = new Map();

        //create enemies
        for (int i = 0; i < 3; ++i) {
            enemies[i] = new Enemies();
            enemies[i]->shot = new Shot();
        }

        gFont = TTF_OpenFont( "Resource/Font/ATARCC__.TTF", 28 );

        //Is Running
        is_running = true;
    }
    else {

        //Is Running
        is_running = false;
    }
}

//Enemies
void Game::MakeEnemies() {

        bool n_add_enemy;
        n_add_enemy = rand() % 1000;

        if (!n_add_enemy && enemies_num < 3) {

            int type = rand() % 4;
            if (type == 2 && score / 10 < 100) {
                type = 1;
            }

            int wall_size;
            if (score >= map->start_wall_break && score <= map->finish_wall_break) {
                wall_size = 256;
            }
            else {
                wall_size = map->size_of_wall;
            }

            if (type == 0 && wall_size == 256) {
                type = 1;
            }

            enemies[last_enemy]->type = type;

            enemies[last_enemy]->Calibrate();

            enemies[last_enemy]->on_screen = 1;

            int x_pos = rand() % (640 - 2 * wall_size - 106);
            x_pos += wall_size + 26 ;

            if (enemies[last_enemy]->type != 2)
                enemies[last_enemy]->ChangeSpeed(0, 3);
            else
                enemies[last_enemy]->ChangeSpeed(10, 3);


            if (enemies[last_enemy]->type == 0) {
                enemies[last_enemy]->Init(x_pos, -enemies[last_enemy]->up, 32, 64);
            } else if (enemies[last_enemy]->type == 1) {
                enemies[last_enemy]->Init(x_pos, -enemies[last_enemy]->up, 32, 32);
            } else if (enemies[last_enemy]->type == 2) {
                enemies[last_enemy]->Init(0, -enemies[last_enemy]->up, 32, 32);
            } else if (enemies[last_enemy]->type == 3) {
                enemies[last_enemy]->Init(x_pos, -enemies[last_enemy]->up, 64, 64);
            }
            enemies_num++;

            last_enemy++;
            last_enemy %= 3;
        }
}


//Update
void Game::Update() {
        if (SDL_GetTicks() - last_get_ticket >= second_per_speed) {
            score++;
            last_get_ticket = SDL_GetTicks();
        }

        //FighterJet Update
        fighter_jet->Update();

        if (SDL_GetTicks() / 30 > fps) {
            fps++;

            //update shot
            if (shot->Fired()) {
                shot->Update();
                shot->ChangeSpeed(0, -20);
            }

            //Delete out of screen shot
            if(shot->des_rec.y < 0)
                shot->fired = 0;

            for (int i = 0; i < 3; ++i) {

                //update enemies
                if (enemies[i]->OnScreen()) {

                    enemies[i]->Update();

                    if (enemies[i]->type != 2)
                        enemies[i]->ChangeSpeed(0, objects_speed);
                    else
                        enemies[i]->ChangeSpeed(10, objects_speed);

                    if (enemies[i]->type == 3 && !enemies[i]->shot->Fired()) {

                        enemies[i]->shot->fired = true;

                        enemies[i]->shot->Init(enemies[i]->des_rec.x + 16, enemies[i]->des_rec.y + 16);

                        enemies[i]->shot->ChangeSpeed(0, 20);
                    }
                }

                //delete out of screen enemies
                if (enemies[i]->des_rec.y + enemies[i]->down > 280) {
                        enemies[i]->on_screen = 0;
                        enemies_num--;
                }

                if (enemies[i]->shot->Fired()) {
                    enemies[i]->shot->Update();
                    enemies[i]->shot->ChangeSpeed(0, 20);
                }
            }
        }

        //Strat The War
        for (int i = 0; i < 3; ++i) {

            //Kill
            if(shot->Fired() //Fired
            && enemies[i]->OnScreen() //enemies on screen

            //Overlap shot & enemies
            && shot->des_rec.y + 22 >= enemies[i]->des_rec.y + enemies[i]->up
            && shot->des_rec.y + 10 <= enemies[i]->des_rec.y + enemies[i]->down
            && shot->des_rec.x + 18 >= enemies[i]->des_rec.x + enemies[i]->left
            && shot->des_rec.x + 14 <= enemies[i]->des_rec.x + enemies[i]->right) {

                //Delete enemies
                if (enemies[i]->type != 0) {
                    enemies[i]->on_screen = 0;
                    enemies_num--;
                }

                //unFired
                shot->fired = 0;
            }

            //Crash
            if( enemies[i]->OnScreen() //enemies on screen

            //Overlab FighterJet & enemies
            && fighter_jet->des_rec.y + 28 >= enemies[i]->des_rec.y + enemies[i]->up
            && fighter_jet->des_rec.y + 4 <= enemies[i]->des_rec.y + enemies[i]->down
            && fighter_jet->des_rec.x + 30 >= enemies[i]->des_rec.x + enemies[i]->left
            && fighter_jet->des_rec.x + 2 <=  enemies[i]->des_rec.x + enemies[i]->right){

                //stop Game
                is_running = false;
            }

            //Sniper
            if( enemies[i]->shot->Fired() //enemies on screen

            //Overlab FighterJet & enemies
            && fighter_jet->des_rec.y + 28 >= enemies[i]->shot->des_rec.y + 10
            && fighter_jet->des_rec.y + 4 <= enemies[i]->shot->des_rec.y + 22
            && fighter_jet->des_rec.x + 30 >= enemies[i]->shot->des_rec.x + 14
            && fighter_jet->des_rec.x + 2 <=  enemies[i]->shot->des_rec.x + 18){

                //stop Game
                is_running = false;
            }

            //if (enemies[i]->OnScreen() && enemies[i]->type == 2 && enemies[i]->des_rec.x + 32 >= map->size_of_wall) {
            //    enemies[i]->on_screen = 0;
            //    enemies_num--;
            //}
            //Delete out of screen shot
            if(enemies[i]->shot->des_rec.y + 22 > 280)
                enemies[i]->shot->fired = 0;
        }

        //lvl update
        if (score - lvl_score > 600) {

            map->Update(score, lvl % 2);

            lvl++;

            lvl_score = score;
        }

        //crash with wall
        if (CollisionWithTheWall(fighter_jet, map, score)) {
            is_running = 0;
        }

        if (score / 10 > 500) {//legendery
            second_per_speed = 2;
            objects_speed = 15;
        }else if (score / 10 > 150) {//pro
            second_per_speed = 5;
            objects_speed = 6;
        } else if (score / 10 > 50) {//nooooooob!!!!!
            second_per_speed = 10;
            objects_speed = 3;
        }


}



//Render
void Game::Render() {

    //River
    SDL_SetRenderDrawColor(renderer, 34, 44, 141, SDL_ALPHA_OPAQUE);

    //Clear Renderer
    SDL_RenderClear(renderer);

    //Renderer Stuffs

    //Map Render
    map->Render(renderer, score);

    //Render FighterJet
    fighter_jet->Render(renderer, "Resource/fighter_jet.png" );

    //Render Shots
    if (shot->Fired())
        shot->Render(renderer, "Resource/shot.png");

    for (int i = 0; i < 3; ++i) {
        if (enemies[i]->OnScreen()) {
            if (enemies[i]->type == 3)
                enemies[i]->Render(renderer, "Resource/tanker.png");
            else if (enemies[i]->type == 2)
                enemies[i]->Render(renderer, "Resource/jet.png");
            else if (enemies[i]->type == 1)
                enemies[i]->Render(renderer, "Resource/helicopter.png");
            else if (enemies[i]->type == 0)
                enemies[i]->Render(renderer, "Resource/barrier.png");
            //cout << i << ' ' << enemies[i]->des_rec.x << ' ' << enemies[i]->des_rec.y << '\n';
        }
        enemies[i]->shot->Render(renderer, "Resource/shot.png");
    }

    //Score Render
    ScoreRender(renderer, score, gFont, high_score);

    //Present Renderer
    SDL_RenderPresent(renderer);
}

//Handel Events
void Game::HandelEvents() {

    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        is_running = 0;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT ) {
        fighter_jet->ChangeSpeed( 10, 0);
    }

    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
        fighter_jet->ChangeSpeed( -10, 0);
    }

    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z && !shot->Fired()) {

        //Fired
        shot->fired = true;

        //located
        shot->Init(fighter_jet->des_rec.x, fighter_jet->des_rec.y);

        //Change Shot speed
        shot->ChangeSpeed(0, -20);
    }
}

//Position Of Running
bool Game::IsRunning() {
    return is_running;
}
