//
// Created by michi on 26/11/2019.
//

#include "Enemies/Enemy.h"

Enemy::Enemy(int givenHealth, std::shared_ptr<Sprite> givenImage) {
    health = givenHealth;
    std::shared_ptr<Sprite> image = givenImage;
}

int Enemy::getHealth() {
    return health;
}

void Enemy::getHit(int damage) {
    health -= damage;
    if (health <= 0) {
        die();
    }
}

void Enemy::die() {
    //moet nog ingevuld worden
}

