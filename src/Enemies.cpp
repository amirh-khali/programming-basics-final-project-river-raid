#include "Enemies.h"

void Enemies::Calibrate() {
    if (type == 0) {
        left = 4;
        right = 60;
        up = 11;
        down = 24;
    } else if (type == 1) {
        left = 0;
        right = 32;
        up = 6;
        down = 26;
    } else if (type == 2) {
        left = 7;
        right = 25;
        up = 13;
        down = 19;
    } else if (type == 3) {
        left = 0;
        right = 64;
        up = 22;
        down = 40;
    }
}

void Enemies::ShotInit() {
    shot->Init(des_rec.x + 16, des_rec.y + 16);
}

void Enemies::ShotUpdate() {

    //update shot
    if (shot->Fired()) {
        shot->Update();
        shot->ChangeSpeed(0, 20);
    }

    //Delete out of screen shot
    if(shot->des_rec.y > 480)
        shot->fired = 0;
}

bool Enemies::OnScreen() {
    return on_screen;
}
