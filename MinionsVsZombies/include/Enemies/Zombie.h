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
    int collisionStart;
    int collisionTime;

public:
    Zombie(int health, int walkingSpeed, int damage, int row, std::unique_ptr<Sprite> image, int creationTime);

    int getWalkingSpeed();
    int getDamage();
    int getRow();
    int getPosition();
    void setPosition(int newPosition);
    int getCreationTime();
    bool setCreationTime(int newCreationTime);

    void walk();

    bool show(bool show);

    inline bool killedUser(){return position == 0;}

    void collide(int time);
    int getCollisionTime(int time);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ZOMBIE_H
