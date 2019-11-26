//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/scene.h>
#include "Minion.h"

Minion::Minion(int givenHealth, int givenCost, int givenCooldownTime, std::unique_ptr<Sprite> givenImage) {
    health = givenHealth;
    cost = givenCost;
    cooldownTime = givenCooldownTime;
    //image = givenImage;
}

int Minion::getHealth() {
    return health;
}

int Minion::getCost() {
    return cost;
}

int Minion::getCooldownTime() {
    return cooldownTime;
}



