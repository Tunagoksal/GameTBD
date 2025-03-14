//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_GHOST_H
#define GAMETBD_GHOST_H

#include <SDL_render.h>
#include "Animation.h"
#include "CollisionManager.h"

class Ghost {
private:
    int x,y;
    Animation ghostA;
    SDL_Rect collider;
    CollisionManager* collisionManager;
    int speed;
public:
    Ghost();
    Ghost(SDL_Texture* texture,int x,int y,CollisionManager* manager);
    void move(float deltaTime);
    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer);
    SDL_Rect getCollider(){return  collider;}
};


#endif //GAMETBD_GHOST_H
