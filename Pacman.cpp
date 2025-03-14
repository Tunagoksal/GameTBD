//
// Created by Tuna on 18.02.2025.
//

#include <iostream>
#include "Pacman.h"
#include <SDL_image.h>

Pacman::Pacman(SDL_Texture *texture,int x,int y,CollisionManager* manager):pacmanA(texture, 16, 16, 42, 200,6,7)  {

    state = REGULAR;
    currentDir = DEFOULT;
    nexDir = DEFOULT;
    this->collisionManager = manager;
    speed = 2;
    this->x = x;
    this->y = y;
    collider = {x, y, 16, 16};
}


void Pacman::update(Uint32 deltaTime) {
    float dt = static_cast<float>(deltaTime);
    pacmanA.update(dt);
    move(dt);
    if(state == IMMORTAL && SDL_GetTicks() - powerUpStart >= powerUpDuration){
        state = REGULAR;
    }
}

void Pacman::render(SDL_Renderer* renderer) {
    pacmanA.render(renderer, x, y);
}

void Pacman::move(float deltaTime) {
    const int tileSize = 16;
    static float movementAccumulator = 0.0f;

    float frameTime = 16.0f;
    float normalizedDeltaTime = deltaTime / frameTime;
    float adjustedSpeed = speed * normalizedDeltaTime;


    movementAccumulator += adjustedSpeed;

    if (movementAccumulator >= tileSize ) {
        movementAccumulator -= tileSize;

        int nextX = x, nextY = y;
        int tempX = x, tempY = y;

        NextPosition(nexDir, tempX, tempY, tileSize);

        SDL_Rect nextCollider = {tempX, tempY, tileSize, tileSize};
        if (!collisionManager->isWallCollision(nextCollider)) {
            currentDir = nexDir;
            nextX = tempX;
            nextY = tempY;
        } else {
            NextPosition(currentDir, nextX, nextY, tileSize);
        }

        SDL_Rect currentCollider = {nextX, nextY, tileSize, tileSize};
        if (!collisionManager->isWallCollision(currentCollider)) {
            x = nextX;
            y = nextY;
        }

        collider.x = x;
        collider.y = y;
    }
}

void Pacman::NextPosition(Pacman::Direction dir,int& posX,int& posY, int tileSize){
    switch (dir) {
        case Pacman::UP:    posY -= tileSize; break;
        case Pacman::DOWN:  posY += tileSize; break;
        case Pacman::LEFT:  posX -= tileSize; break;
        case Pacman::RIGHT: posX += tileSize; break;
        default:    break;
    }
}

void Pacman::setDirection(Pacman::Direction dir) {
    if (x % 16 == 0 && y % 16 == 0) {
        if(currentDir == DEFOULT){
            currentDir = dir;
        }
        nexDir = dir;
    }
}

void Pacman::turnImmortal() {
    state = IMMORTAL;
    powerUpStart = SDL_GetTicks();
}
