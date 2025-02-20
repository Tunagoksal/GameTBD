//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_PACMAN_H
#define GAMETBD_PACMAN_H


#include <SDL_render.h>
#include "Animation.h"

class Pacman {
public:
    enum Direction{UP,DOWN,LEFT,RIGHT};

    Pacman(SDL_Texture* texture);
    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer);
    void move(float deltaTime);
    void userInput();
    void setDirection(Direction dir);

private:

    int x,y;
    int speed;
    Animation pacmanA;
    Direction currentDir;

    enum States{regular,immortal};
};


#endif //GAMETBD_PACMAN_H
