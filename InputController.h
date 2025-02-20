//
// Created by Tuna on 20.02.2025.
//

#ifndef GAMETBD_INPUTCONTROLLER_H
#define GAMETBD_INPUTCONTROLLER_H

class InputController
{
public:
    void handleInput(Pacman & pacman){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case SDLK_UP: pacman.setDirection(Pacman::UP); break;
                    case SDLK_DOWN: pacman.setDirection(Pacman::DOWN); break;
                    case SDLK_LEFT: pacman.setDirection(Pacman::LEFT); break;
                    case SDLK_RIGHT: pacman.setDirection(Pacman::RIGHT  ); break;
                }
            }
        }
    }
    bool isGameRunning() const{ return quit;}
private:
    bool quit = false;
};

#endif //GAMETBD_INPUTCONTROLLER_H
