//
// Created by matthias on 1/7/20.
//

#include "Minions/BananaMinion.h"

void BananaMinion::shoot() {
    totalShot++;

    int healthPercentage = getHealth() * 100 / getMaxHealth();

    if (healthPercentage > 70) {
        this->getSprite()->animateToFrame(0);
    } else if (healthPercentage > 30) {
        this->getSprite()->animateToFrame(1);
    } else {
        this->getSprite()->animateToFrame(2);
    }
}
