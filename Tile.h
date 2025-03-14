//
// Created by Tuna on 2.03.2025.
//

#ifndef GAMETBD_TILE_H
#define GAMETBD_TILE_H

class Tile{
public:
    Tile(int x, int y, int tileType) : tileType(tileType) {
        collider = {x, y, 16, 16};
    }

    void render(SDL_Renderer* renderer, SDL_Texture* texture) const {
        SDL_RenderCopy(renderer, texture, nullptr, &collider);
    }

    int getType() const { return tileType; }
    SDL_Rect getCollider() const {return  collider;}

private:
    int x,y;
    SDL_Rect collider;
    int tileType;
};

#endif //GAMETBD_TILE_H
