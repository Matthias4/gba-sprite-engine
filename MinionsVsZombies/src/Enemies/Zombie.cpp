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

void Zombie::setPosition(int newPosition){
    position = newPosition;
}

int Zombie::getCreationTime() {
    return creationTime;
}

bool Zombie::setCreationTime(int newCreationTime) {
    return creationTime = newCreationTime;
}

void Zombie::walk() {
    if(position > -32)
    {
        position -= walkingSpeed;
    }
}

bool Zombie::show(bool show)
{
    bool backAtOrigin = false;
    if(show) {
        position -= walkingSpeed;
    } else {
        position += walkingSpeed;
        backAtOrigin = true;
    }
    return backAtOrigin;
}
