//
// Created by Tuna on 1.03.2025.
//

#ifndef GAMETBD_COLLISIONMANAGER_H
#define GAMETBD_COLLISIONMANAGER_H


#include "Map.h"
#include "Tile.h"

class CollisionManager {
public:
    CollisionManager(Map* map);
    bool isWallCollision(const SDL_Rect& collider);
    bool isEntityCollison(const SDL_Rect& colliderOne,const SDL_Rect& colliderTwp);

private:
    Map* map;
};


#endif //GAMETBD_COLLISIONMANAGER_H
