//
// Created by michi on 26/11/2019.
//

#include "Enemies/Enemy.h"

Enemy::Enemy(int givenHealth) {
    health = givenHealth;
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

