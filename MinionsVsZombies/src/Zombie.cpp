//
// Created by michi on 26/11/2019.
//

#include "Zombie.h"

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

void Zombie::walk() {//FIXME: Volgens mij niet nodig: Level past de locatiearray aan (en geeft de sprite waarschijnlijk een nieuwe positie)
    // wandel wandel
    //position--; ofzo
}
