//
// Created by michi on 12/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BULLET_H
#define GBA_SPRITE_ENGINE_PROJECT_BULLET_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Bullet {
private:
    int originalPositionX;
    int creationTime;
    int row;

    std::unique_ptr<Sprite> image;
public:
    Bullet(int originalPositionX, int creationTime, int row, std::unique_ptr<Sprite> image);

    int getOriginalPositionX();
    int getCreationTime();
    int getRow();

    Sprite *getSprite();
    void move(int x, int y);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BULLET_H
