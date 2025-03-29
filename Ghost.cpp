//
// Created by Tuna on 18.02.2025.
//

#include "Ghost.h"


Ghost::Ghost(SDL_Texture *texture, int x, int y, CollisionManager *manager):ghostA(texture, 16, 16, 1, 200,1,1) {
    state = GHOST;

    this->collisionManager = manager;
    speed = 1;
    this->x = x;
    this->y = y;
    startPoint.x = x;
    startPoint.y = y;
    collider = {x, y, 16, 16};
}

void Ghost::move(float deltaTime) {
    const int tileSize = 16;
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
        }

        SDL_Rect nextCollider = {nextX, nextY, tileSize, tileSize};

        if (!collisionManager->isWallCollision(nextCollider)) {
            x = nextX;
            y = nextY;
            collider.x = x;
            collider.y = y;
        } else {
            randomDir = rand() % 4;
        }

    }
}

void Ghost::update(Uint32 deltaTime) {
    float dt = static_cast<float>(deltaTime);
    ghostA.update(dt);

    switch (state) {
        case GHOST:
            break;

        case SCARED:
            if (scaredTimer > 0) {
                scaredTimer -= deltaTime;
                if (scaredTimer <= 0) {
                    state = GHOST;
                }
            }
            break;

        case EYES:
            //TODO you can see the logic missing here add a return to start posiion logic
            x = startPoint.x;
            y = startPoint.y;
            collider.x = x;
            collider.y = y;
            if (x == startPoint.x && y == startPoint.y) {
                state = GHOST;
            }
            break;
    }
    move(dt);
}

void Ghost::render(SDL_Renderer* renderer) {
    ghostA.render(renderer,x,y);
}

void Ghost::makeScared() {
    if (state != EYES) {
        state = SCARED;
        scaredTimer = scaredDuration;
    }
}

void Ghost::gotEaten() {
    state = EYES;
}

SDL_Rect Ghost::getNextCollider() const {
    int nextX = x, nextY = y;

    switch (randomDir) {
        case 0:  nextX -= 16; break;
        case 1:  nextX += 16; break;
        case 2:  nextY -= 16; break;
        case 3:  nextY += 16; break;
    }
    return {nextX, nextY, 16, 16};
}

void Ghost::setRandomDirection() {
    randomDir = rand() % 4;
}
