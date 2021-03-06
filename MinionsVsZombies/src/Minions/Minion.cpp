//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/scene.h>
#include "Minions/Minion.h"

Minion::Minion(int type, int health, int cost, int cooldownTime, std::unique_ptr<Sprite> image, int creationTime) {
    this->type = type;
    this->health = health;
    this->maxHealth = health;
    this->cost = cost;
    this->cooldownTime = cooldownTime;
    this->image = std::move(image);// An unique_ptr cannot be moved, std::move solves this problem https://stackoverflow.com/questions/6876751/differences-between-unique-ptr-and-shared-ptr
    this->creationTime = creationTime;
}

int Minion::getHealth() {
    return health;
}

void Minion::takeDamage(int damage){
    health -= damage;
}

int Minion::getMaxHealth() {
    return maxHealth;
}

int Minion::getCost() {
    return cost;
}

int Minion::getCooldownTime() {
    return cooldownTime;
}

int Minion::getTotalShot() {
    return totalShot;
}

Sprite *Minion::getSprite() {
    return image.get();
}

void Minion::move(int x, int y) {
    image->moveTo(x, y);
}

void Minion::stopAnimtation() {
    image->stopAnimating();
    image->animateToFrame(0);
}



