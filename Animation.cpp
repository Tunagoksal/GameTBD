#include "Animation.h"


Animation::Animation(SDL_Texture* texture, int frameWidth, int frameHeight) {
    this->sprite = texture;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
}
void Animation::render(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect srcFrame = {frameWidth*currentFrame, 0,frameWidth,frameHeight };
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
