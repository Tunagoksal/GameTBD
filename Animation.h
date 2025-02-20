//
// Created by Tuna on 4.02.2025.
//

#ifndef GAMETBD_ANIMATION_H
#define GAMETBD_ANIMATION_H

#include "Texture.h"

class Animation
{
public:
    Animation(SDL_Texture* texture,int frameWidth,int frameHeight,int frames,int speed,int rows,int columns);
    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer, int x, int y);

private:
    SDL_Texture* sprite;
    int frameNum;
    int frameWidth,frameHeight;
    int rowNum,columnNum;
    int speed;
    int currentFrame;
    Uint32 elapsedTime;

};



#endif //GAMETBD_ANIMATION_H
