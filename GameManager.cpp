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

    SDL_Texture *pacmanSprite = loadTexture("D:/C++/projects/GameTBD/assets/pacman.png", renderer);
    SDL_Texture *ghostSprite = loadTexture("D:/C++/projects/GameTBD/assets/red_ghost.png", renderer);
    SDL_Texture *powerUpSprite = loadTexture("D:/C++/projects/GameTBD/assets/powerUp.png", renderer);

    running = true;
    gameMap.loadMap("D:/C++/projects/GameTBD/map.JSON", tileTextures);    // Load map from JSON

    powerUps.resize(gameMap.getPowerUpPositions().size());

    for (int i = 0; i < powerUps.size(); ++i) {
        powerUps[i] = new PowerUp(powerUpSprite,gameMap.getPowerUpPositions()[i].x,gameMap.getPowerUpPositions()[i].y);
    }

    pacman = new Pacman(pacmanSprite,gameMap.getPacmanPos().x,gameMap.getPacmanPos().y,collisionManager);
    ghosts = new Ghost(ghostSprite,gameMap.getGhostPos().x,gameMap.getGhostPos().y,collisionManager);

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
    if (ghosts) {
        delete ghosts;
        ghosts = nullptr;
    }
    for (PowerUp* &powerUp : powerUps) {
        delete powerUp;
        powerUp = nullptr;
    }
    powerUps.clear();
    for (int i = 0; i < 4; i++) {
        if (tileTextures[i]) {
            SDL_DestroyTexture(tileTextures[i]);
            tileTextures[i] = nullptr;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameManager::render() {

    SDL_RenderClear(renderer);
    gameMap.render(renderer);
    pacman->render(renderer);
    if(ghosts){
        ghosts->render(renderer);
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
    ghosts->update(deltaTime);

    if (collisionManager->isEntityCollison(pacman->getCollider(), ghosts->getCollider())) {

        switch (pacman->getState()) {
            case Pacman::REGULAR:
                running = false;
                break;
            case Pacman::IMMORTAL:
                if(ghosts->getState() == Ghost::SCARED){
                    ghosts->setState(Ghost::EYES);
                }else if (ghosts->getState() == Ghost::GHOST){
                    running = false;
                }
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < powerUps.size(); ++i) {
        if(collisionManager->isEntityCollison(pacman->getCollider(),powerUps[i]->getCollider())){
            pacman->setState(Pacman::IMMORTAL);
            ghosts->setState(Ghost::SCARED);
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



