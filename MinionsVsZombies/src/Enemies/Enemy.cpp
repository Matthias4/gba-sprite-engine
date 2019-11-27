//
// Created by michi on 26/11/2019.
//

#include "Enemies/Enemy.h"

int Enemy::getHealth() {
    return health;
}

void Enemy::getHit(int damage) {
    health -= damage;// Wat als health onder 0 gaat? Zie volgende regel. Het maakt niet uit of die onder 0 gaat, zombie gaat toch gewoon dood ;)
    if (health <= 0) {
        die();
    }
}

void Enemy::die() {
    //moet nog ingevuld worden
}

Enemy::Enemy(int givenHealth) {
    health = givenHealth;
}
