//
// Created by Tuna on 18.02.2025.
//

#ifndef GAMETBD_GHOST_H
#define GAMETBD_GHOST_H


class Ghost {
private:
    int x,y;
    Animation ghostA;
public:
    Ghost();
    void update();
    void render();
};


#endif //GAMETBD_GHOST_H
