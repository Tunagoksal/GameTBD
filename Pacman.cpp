//
// Created by Tuna on 18.02.2025.
//

#include "Pacman.h"
#include <SDL_image.h>

Pacman::Pacman(SDL_Texture* texture):pacmanA(texture, 64, 64, 42, 100,6,7) {

    speed = 1;
    x = 100;
    y = 100;
}

void Pacman::update(Uint32 deltaTime) {
    pacmanA.update(deltaTime);
    move(deltaTime);
}

void Pacman::render(SDL_Renderer* renderer) {
    pacmanA.render(renderer, x, y);
}

// ok so pacman might have a tile movement system where it moves tile by tile so u may want to adjust this in the future
//how to do it first change your x and y in pacman with tile coordinates and increment or decrement them by one in the same manner
//also have a queued direction and change the implementation of update for that
void Pacman::move(float deltaTime) {

    float adjustedSpeed = speed * deltaTime;

    switch (currentDir) {
        case UP: y -= adjustedSpeed; break;
        case DOWN: y += adjustedSpeed; break;
        case LEFT: x -= adjustedSpeed; break;
        case RIGHT: x += adjustedSpeed; break;
    }
}

void Pacman::setDirection(Pacman::Direction dir) {
    this->currentDir = dir;
}