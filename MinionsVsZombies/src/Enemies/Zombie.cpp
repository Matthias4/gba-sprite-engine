//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "Enemies/Zombie.h"

Zombie::Zombie(int givenHealth, int givenWalkingSpeed, int givenDamage, int givenRow, std::unique_ptr<Sprite> image, int creationTime)
        : Enemy(givenHealth, std::move(image)) {
    walkingSpeed = givenWalkingSpeed;
    damage = givenDamage;
    row = givenRow;
    position = GBA_SCREEN_WIDTH;
    this->creationTime = creationTime;
}

int Zombie::getWalkingSpeed() {
    return walkingSpeed;
}

int Zombie::getDamage() {
    return damage;
}

int Zombie::getRow() {
    return row;
}

int Zombie::getPosition() {
    return position;
}

int Zombie::getCreationTime() {
    return creationTime;
}

void Zombie::walk() {
    // wandel wandel
    // (•_•)
    // ( •_•)⌐■-■
    // (⌐■_■)
    //position--; ofzo

    position -= walkingSpeed;// #matthias: position -= walkSpeed; ofzo?
}

void Zombie::show(bool show)
{
    if(show) {
        position -= walkingSpeed;
    } else {
        position += walkingSpeed;
    }
}
