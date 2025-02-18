//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_PACMAN_H
#define GAMETBD_PACMAN_H


class Pacman {
private:
 int x,y;
 Animation pacmanA;

public:
    Pacman();
    void update();
    void render();

};


#endif //GAMETBD_PACMAN_H
