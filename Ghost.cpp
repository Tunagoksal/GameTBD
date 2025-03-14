//
// Created by Tuna on 18.02.2025.
//

#include "Ghost.h"


Ghost::Ghost(SDL_Texture *texture, int x, int y, CollisionManager *manager):ghostA(texture, 16, 16, 42, 200,6,7) {
    this->collisionManager = manager;
    speed = 2;
    this->x = x;
    this->y = y;
    collider = {x, y, 16, 16};
}

void Ghost::move(float deltaTime) {
    int randomDir = rand() % 5;

    const int tileSize = 16;
    static float movementAccumulator = 0.0f;

    float frameTime = 16.0f;
    float normalizedDeltaTime = deltaTime / frameTime;
    float adjustedSpeed = speed * normalizedDeltaTime;


    movementAccumulator += adjustedSpeed;

    if (movementAccumulator >= tileSize) {
        movementAccumulator -= tileSize;

        int nextX = x, nextY = y;

        switch (randomDir) {
            case 0:  nextX -= tileSize; break;
            case 1:  nextX += tileSize; break;
            case 2:  nextY -= tileSize; break;
            case 3:  nextY += tileSize; break;
            default:    break;
        }

        SDL_Rect nextCollider = {nextX, nextY, tileSize, tileSize};
        if (!collisionManager->isWallCollision(nextCollider)) {
            x = nextX;
            y = nextY;
        }
        else{
            randomDir = rand() % 5;
        }

        collider.x = x;
        collider.y = y;
    }

}

void Ghost::update(Uint32 deltaTime) {
    float dt = static_cast<float>(deltaTime);
    ghostA.update(dt);
    move(dt);
}

void Ghost::render(SDL_Renderer* renderer) {
    ghostA.render(renderer,x,y);
}


