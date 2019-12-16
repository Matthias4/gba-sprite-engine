//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H
#define GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "Enemies/Enemy.h"

class Zombie: public Enemy {
private:
    int walkingSpeed;
    int damage;
    int row;
    int position;
    int creationTime;

public:
    Zombie(int health, int walkingSpeed, int damage, int row, std::unique_ptr<Sprite> image, int creationTime);

    int getWalkingSpeed();
    int getDamage();
    int getRow();
    int getPosition();
    int getCreationTime();

    void walk();
    void increaseWalkingSpeed();

    void show(bool show);

    inline bool killedUser(){return position == 0;}
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H
