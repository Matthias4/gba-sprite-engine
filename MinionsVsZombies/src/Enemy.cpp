//
// Created by michi on 26/11/2019.
//

#include "Enemy.h"

int Enemy::getHealth() {
    return health;
}

void Enemy::getHit(int damage) {
    health -= damage;//FIXME: Wat als health onder 0 gaat?
}
