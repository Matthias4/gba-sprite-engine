//
// Created by michi on 26/11/2019.
//

#include "Minions/FlowerMinion.h"

int FlowerMinion::getSunPower() {
    return sunPower;
}

int FlowerMinion::getProductionRate() {
    return productionRate;
}

void FlowerMinion::produceSun() {
    //nog te implementeren
}

void FlowerMinion::shoot() {
    produceSun();// Flower minion is harmless. Instead of firing deadly banana's at zombies, it produces beautiful flowers :)
}