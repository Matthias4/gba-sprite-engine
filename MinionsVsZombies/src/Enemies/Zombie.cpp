//
// Created by michi on 26/11/2019.
//

#include "Enemies/Zombie.h"

Zombie::Zombie(int givenHealth, int givenWalkingSpeed, int givenDamage, int givenRow, int givenPosition, std::shared_ptr<Sprite> givenImage)
        : Enemy(givenHealth, givenImage)
{
    walkingSpeed = givenWalkingSpeed;
    damage = givenDamage;
    row = givenRow;
    position = givenPosition;

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

void Zombie::walk() {
    // wandel wandel
    //position--; ofzo
}

