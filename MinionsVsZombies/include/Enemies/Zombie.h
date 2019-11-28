//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H
#define GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H

#include "Enemies/Enemy.h"

class Zombie: public Enemy {
private:
    int walkingSpeed;
    int damage;
    int row;
    int position;
public:
    int getWalkingSpeed();
    int getDamage();
    int getRow();
    int getPosition();

    Zombie(int health, int walkingSpeed, int damage, int row, int position);

    void walk();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H