//
// Created by Tuna on 26.02.2025.
//

#include "GameManager.h"
#include <iostream>

bool GameManager::init(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Initialization failed!\n";
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window creation failed!\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cout << "Renderer creation failed!\n";
        return false;
    }

    collisionManager = new CollisionManager(&gameMap);

    SDL_Texture* floorTexture = loadTexture("D:/C++/projects/GameTBD/assets/Dune_Caladan_MattRhodes-1100x441.bmp", renderer);
    SDL_Texture* wallTexture = loadTexture("D:/C++/projects/GameTBD/assets/Tile1.png", renderer);

    if (!floorTexture || !wallTexture) {
        std::cerr << "ERROR: Failed to load textures.\n";
        return false;
    }

    tileTextures[0] = floorTexture;
    tileTextures[1] = wallTexture;

    running = true;
    gameMap.loadMap("D:/C++/projects/GameTBD/map.JSON", tileTextures);    // Load map from JSON

    powerUps.resize(gameMap.getPowerUpPositions().size());
    ghosts.resize(gameMap.getGhostsPos().size());

    SDL_Texture *pacmanSprite = loadTexture("D:/C++/projects/GameTBD/assets/pacman.png", renderer);
    SDL_Texture *powerUpSprite = loadTexture("D:/C++/projects/GameTBD/assets/powerUp.png", renderer);

    //TODO write a wrapper class for texture
    ghostSprite[0] = loadTexture("D:/C++/projects/GameTBD/assets/red_ghost.png", renderer);
    ghostSprite[1] = loadTexture("D:/C++/projects/GameTBD/assets/pink_ghost.png", renderer);
    ghostSprite[2] = loadTexture("D:/C++/projects/GameTBD/assets/blue_ghost.png", renderer);
    ghostSprite[3] = loadTexture("D:/C++/projects/GameTBD/assets/orange_ghost.png", renderer);

    for (int i = 0; i < powerUps.size(); ++i) {
        powerUps[i] = new PowerUp(powerUpSprite,gameMap.getPowerUpPositions()[i].x,gameMap.getPowerUpPositions()[i].y);
    }
    for (int i = 0; i < ghosts.size(); ++i) {
        ghosts[i] = new Ghost(ghostSprite[i],gameMap.getGhostsPos()[i].x,gameMap.getGhostsPos()[i].y,collisionManager);
    }
    //TODO ghost problem might be causes by the collision manager or giving the same instance of collision manager to all

    pacman = new Pacman(pacmanSprite,gameMap.getPacmanPos().x,gameMap.getPacmanPos().y,collisionManager);
    //ghost = new Ghost(ghostSprite,gameMap.getGhostPos().x,gameMap.getGhostPos().y,collisionManager);

    return true;

}

void GameManager::run() {
    Uint32 lastTime = SDL_GetTicks();
    InputController inputController;

    while (running){
        Uint32 currentTime = SDL_GetTicks();
        int deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        inputController.handleInput(*pacman);
        running = inputController.isGameRunning();

        update(deltaTime);
        render();
    }
}

void GameManager::cleanup() {
    delete pacman;
    pacman = nullptr;

    //TODO write a wrapper class for texture
    for (int i = 0; i < 4; ++i) {
        if (ghostSprite[i]) {
            SDL_DestroyTexture(ghostSprite[i]);
            ghostSprite[i] = nullptr;
        }
    }

    for (PowerUp* &powerUp : powerUps) {
        delete powerUp;
        powerUp = nullptr;
    }
    for (Ghost* &ghost : ghosts) {
        delete ghost;
        ghost = nullptr;
    }
    powerUps.clear();
    for (int i = 0; i < 4; i++) {
        if (tileTextures[i]) {
            SDL_DestroyTexture(tileTextures[i]);
            tileTextures[i] = nullptr;
        }
    }

    delete collisionManager;
    collisionManager = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameManager::render() {

    SDL_RenderClear(renderer);
    gameMap.render(renderer);
    pacman->render(renderer);
    /*if(ghost){
        ghost->render(renderer);
    }*/

    for (auto& ghost : ghosts) {
        if(ghost){
            ghost->render(renderer);
        }
    }
    for (int i = 0; i < powerUps.size(); i++) {
        if (powerUps[i]) {
            powerUps[i]->render(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}

void GameManager::update(int deltaTime) {

    pacman->update(deltaTime);
    //ghost->update(deltaTime);

    for (int i = 0; i < ghosts.size(); ++i) {
        ghosts[i]->update(deltaTime);
        std::cout << "Ghost " << i << " at: "
                  << ghosts[i]->getCollider().x << ", "
                  << ghosts[i]->getCollider().y << std::endl;
    }

    for (auto& ghost : ghosts) {

        SDL_Rect proposed = ghost->getNextCollider();
        if (!collisionManager->isWallCollision(proposed) &&
            !willCollideWithOtherGhost(ghost, proposed.x, proposed.y)) {
            ghost->update(deltaTime); // this includes move()
        } else {
            // maybe reroll direction or skip movement this frame
            ghost->setRandomDirection();
        }

        if (collisionManager->isEntityCollison(pacman->getCollider(), ghost->getCollider())) {

            switch (pacman->getState()) {
                case Pacman::REGULAR:
                    running = false;
                    break;
                case Pacman::IMMORTAL:
                    if(ghost->getState() == Ghost::SCARED){
                        ghost->gotEaten();
                    }else if (ghost->getState() == Ghost::GHOST){
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < powerUps.size(); ++i) {
        if(collisionManager->isEntityCollison(pacman->getCollider(),powerUps[i]->getCollider()) && powerUps[i]->getActive()){
            pacman->turnImmortal();
            for (auto& ghost : ghosts) {ghost->makeScared();}
            powerUps[i]->setActive(false);
        }
    }
}

SDL_Texture *GameManager::loadTexture(const string &path, SDL_Renderer *renderer) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!newTexture) {
        std::cerr << "Unable to load texture at " << path << " SDL_image Error: " << IMG_GetError() << "\n";
    } else {
        std::cout << "Successfully loaded texture: " << path << "\n";
    }
    return newTexture;
}

bool GameManager::willCollideWithOtherGhost(Ghost* current, int nextX, int nextY) {
    SDL_Rect nextCollider = {nextX, nextY, 16, 16};
    for (Ghost* other : ghosts) {
        SDL_Rect otherCollider = other->getCollider();
        if (other != current) {
            if (SDL_HasIntersection(&nextCollider, &otherCollider)) {
                return true;
            }
        }
    }
    return false;
}


