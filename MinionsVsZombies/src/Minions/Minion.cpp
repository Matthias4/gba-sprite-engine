//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/scene.h>
#include "Minions/Minion.h"

Minion::Minion(int givenHealth, int givenCost, int givenCooldownTime, std::unique_ptr<Sprite> givenImage) {
    health = givenHealth;
    cost = givenCost;
    cooldownTime = givenCooldownTime;
    image = std::move(givenImage);// An unique_ptr cannot be moved, std::move solves this problem https://stackoverflow.com/questions/6876751/differences-between-unique-ptr-and-shared-ptr
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

Sprite *Minion::getSprite() {
    return image.get();
}

void Minion::move(int x, int y) {
    image->moveTo(x, y);
}



