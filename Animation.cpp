#include "Animation.h"


Animation::Animation(SDL_Texture* texture, int frameWidth, int frameHeight, int frames,int speed,int rows,int columns) {
    this->sprite = texture;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameNum=frames;
    this->speed = speed;
    this->rowNum = rows;
    this->columnNum = columns;
}
void Animation::render(SDL_Renderer* renderer, int x, int y) {
    if (!sprite) return;

    int col = currentFrame%columnNum;
    int row =  currentFrame/columnNum;

    SDL_Rect srcFrame = {col*frameWidth, row*frameHeight,frameWidth,frameHeight };
    SDL_Rect destFrame = {x,y,frameWidth,frameHeight};
    SDL_RenderCopy(renderer,sprite,&srcFrame,&destFrame);
}
void Animation::update(Uint32 deltaTime) {
    elapsedTime += deltaTime;
    if(elapsedTime >= speed){
        elapsedTime = 0;
        currentFrame = (currentFrame + 1) % frameNum;
    }
}
