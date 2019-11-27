//
// Created by michi on 26/11/2019.
//

#include "Enemies/Zombie.h"

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

Zombie::Zombie(int givenHealth, int givenWalkingSpeed, int givenDamage, int givenRow, int givenPosition)
: Enemy(givenHealth)
{
    walkingSpeed = givenWalkingSpeed;
    damage = givenDamage;
    row = givenRow;
    position = givenPosition;
}

