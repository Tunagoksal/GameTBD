//
// Created by Tuna on 20.03.2025.
//

#ifndef GAMETBD_POWERUP_H
#define GAMETBD_POWERUP_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//actually for the current system of the game having a class for powerUps is unneccesary in my opinion just keeping them so maybe i can
class PowerUp {
public:
    PowerUp(SDL_Texture *texture,int x,int y){
        this->texture = texture;
        this->x = x;
        this->y = y;
        collider = {x, y, 16, 16};
    };
    void render(SDL_Renderer *renderer) {
        if (active) {
            SDL_RenderCopy(renderer, texture, nullptr, &collider);
        }
    }
    void setActive(bool state){active = state;}
    bool getActive() const{return active;}
    SDL_Rect getCollider(){return  collider;}

private:
    SDL_Texture *texture;
    SDL_Rect collider;
    int x,y;
    bool active = true;
};


#endif //GAMETBD_POWERUP_H
