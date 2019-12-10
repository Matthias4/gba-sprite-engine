//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include "Enemies/Enemy.h"

/*Enemy::Enemy(int givenHealth, std::unique_ptr<Sprite> givenImage) {
    health = givenHealth;
    image = std::move(givenImage);
}*/

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

void Enemy::move(int x, int y) {
    image->moveTo(x, y);
}

