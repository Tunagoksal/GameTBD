//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_GHOST_H
#define GAMETBD_GHOST_H

#include <SDL_render.h>
#include "Animation.h"
#include "CollisionManager.h"

class Ghost {
public:
    enum State{GHOST,SCARED,EYES};

    Ghost();
    Ghost(SDL_Texture* texture,int x,int y,CollisionManager* manager);

    void move(float deltaTime);
    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer);
    SDL_Rect getCollider(){return  collider;}
    void setState(State state){
        this->state = state;
    }
    State getState(){return state;}

private:
    int x,y;
    Animation ghostA;
    SDL_Rect collider;
    CollisionManager* collisionManager;
    int speed;
    State state;


};


#endif //GAMETBD_GHOST_H
