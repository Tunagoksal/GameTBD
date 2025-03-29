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

    SDL_Rect getNextCollider() const;
    void setRandomDirection();

    void makeScared();
    void gotEaten();

private:
    int x,y;
    SDL_Point startPoint;
    Animation ghostA;
    SDL_Rect collider;
    CollisionManager* collisionManager;
    int speed;
    State state;

    float movementAccumulator = 0.0f;
    int randomDir = rand() % 4;

    Uint32 scaredTimer = 0;
    Uint32 scaredDuration = 10000;

};


#endif //GAMETBD_GHOST_H
