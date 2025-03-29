//
// Created by Tuna on 1.03.2025.
//
#include "Map.h"

bool Map::loadMap(const std::string &filename, SDL_Texture* textures[]) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return false;
    }

    nlohmann::json data;
    file >> data;
    vector<string> mapData = data["map"];

    height = mapData.size();
    width = mapData[0].size();

    for (int i = 0; i < 2; ++i) {
        tileTextures[i] = textures[i];
    }

    for (int i = 0; i < height; ++i) {
        std::vector<Tile> rowTiles;
        for (int j = 0; j < width; ++j) {
            char tile = mapData[i][j];
            int x = j * tile_size;
            int y = i * tile_size;

            int  type=0;

            if (tile == '#') {
                type = 1;
            }
            if (tile == '*') {
                powerUpPos.push_back({x,y});
            }
            if (tile == 'P') {
                pacmanPos = {x, y};
            }
            else if (tile == 'G') {
                ghostsPos.push_back({x,y});
                GhostPos = {x, y};
            }
            if (type != 0) {
                rowTiles.emplace_back(x, y, type);
            }
        }
        tiles.push_back(rowTiles);
    }
    return true;
}

void Map::render(SDL_Renderer* renderer) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int type = tiles[row][col].getType();
            if (type > 0 && type < 2 && tileTextures[type]) {
                tiles[row][col].render(renderer, tileTextures[type]);
            }
        }
    }
}
