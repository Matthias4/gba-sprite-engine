//
// Created by michi on 26/11/2019.
//

#include "Enemies/Enemy.h"

int Enemy::getHealth() {
    return health;
}

void Enemy::getHit(int damage) {
    health -= damage;//FIXME: Wat als health onder 0 gaat?
    if (health == 0) {
        die();
    }
}

void Enemy::die() {
    //moet nog ingevuld worden
}
