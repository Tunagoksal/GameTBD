//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_PACMAN_H
#define GAMETBD_PACMAN_H


#include <SDL_render.h>
#include "Animation.h"
#include "CollisionManager.h"

class Pacman {
public:
    enum Direction{DEFOULT,UP,DOWN,LEFT,RIGHT};
    enum State{REGULAR,IMMORTAL};

    Pacman();
    Pacman(SDL_Texture* texture,int x,int y,CollisionManager* manager);

    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer);
    void move(float deltaTime);
    void setDirection(Direction dir);
    void turnImmortal();

    int getX(){return x;}
    int getY(){return y;}

    void setPosition(int x,int y){
        this->x = x;
        this->collider.x = x;
        this->y = y;
        this->collider.y = y;
    }

    SDL_Rect getCollider(){return  collider;}
    State getState(){return state;}


private:

    int x,y;
    int speed;
    Animation pacmanA;
    Direction currentDir;
    Direction nexDir;
    SDL_Rect collider;
    CollisionManager* collisionManager;

    State state;
    Uint32 powerUpStart = 0;
    Uint32 powerUpDuration = 5000;


    void NextPosition(Direction dir, int& posX, int& posY, int tileSize);
};


#endif //GAMETBD_PACMAN_H
