//
// Created by michi on 26/11/2019.
//

#include "Minions/FlowerMinion.h"

int FlowerMinion::getSunPower() {
    return sunPower;
}

void FlowerMinion::produceSun() {
    this->getSprite()->animate();
}

void FlowerMinion::shoot() {
    totalShot++;
    produceSun();// Flower minion is harmless. Instead of firing deadly banana's at zombies, it produces beautiful flowers :)
}