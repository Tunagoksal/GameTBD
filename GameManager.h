#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Pacman.h"
#include "Ghost.h"
#include "PowerUp.h"
#include "Map.h"
#include "InputController.h"
#include "CollisionManager.h"
#include "Animation.h"

class GameManager {
public:

    bool init(const char* title, int width, int height);
    void run();
    void cleanup();
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    void handlePacmanGhostCollision(Pacman* pacman, Ghost* ghost, bool& running);

private:
    void handleEvents();
    void update(int deltaTime);
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Map gameMap;
    SDL_Texture* tileTextures[2];
    SDL_Texture* ghostSprite[4];

    Pacman *pacman;
    vector<Ghost*> ghosts;
    vector<PowerUp*> powerUps;
    CollisionManager *collisionManager;

    //TODO  this collision stuff are everywhere change it !!!
    bool willCollideWithOtherGhost(Ghost *current, int nextX, int nextY);
};

#endif
