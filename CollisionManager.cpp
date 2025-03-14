//
// Created by Tuna on 1.03.2025.
//

#include "CollisionManager.h"

CollisionManager::CollisionManager(Map* map) {
    this->map = map;
}


bool CollisionManager::isWallCollision(const SDL_Rect& collider) {
    for (const auto& row : map->getTiles()) {
        for (const auto& tile : row) {
            SDL_Rect tileCollider = tile.getCollider();
            if (tile.getType() == 1) {
                if (SDL_HasIntersection(&collider, &tileCollider)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool CollisionManager::isEntityCollison(const SDL_Rect &colliderOne, const SDL_Rect &colliderTwp) {
    if(SDL_HasIntersection(&colliderOne, &colliderTwp)){
        return true;
    }
    return false;
}
