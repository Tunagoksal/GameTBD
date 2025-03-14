//
// Created by Tuna on 26.02.2025.
//

#ifndef GAMETBD_MAP_H
#define GAMETBD_MAP_H

#include <SDL.h>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include "Tile.h"

using namespace std;

class Map {
public:
    bool loadMap(const std::string& filename,SDL_Texture* textures[]);
    void render(SDL_Renderer* renderer);

    SDL_Point getPacmanPos(){return pacmanPos;}
    SDL_Point getGhostPos(){return GhostPos;}

    vector<vector<Tile>>& getTiles(){
        return tiles;
    }

private:
    int width,height;
    SDL_Point pacmanPos;
    SDL_Point GhostPos;
    SDL_Point *powerUpPositions;
    vector<vector<Tile>> tiles;
    int tile_size = 16;
    SDL_Texture* tileTextures[2];
};

#endif //GAMETBD_MAP_H
