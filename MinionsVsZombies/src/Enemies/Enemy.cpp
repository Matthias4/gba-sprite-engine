//
// Created by michi on 26/11/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <Level/Zombie.h>
#include <libgba-sprite-engine/palette/palette_manager.h>

#include "Enemies/Enemy.h"
#include "Level/LevelFGPalette.h"

Enemy::Enemy(int givenHealth, void* givenSpriteData, SpriteSize givenSpriteSize, int givenNumberOfFrames, int givenAnimationDelay) {
    health = givenHealth;

    SpriteBuilder<Sprite> spriteBuilder;
    std::shared_ptr<Sprite> image = spriteBuilder
            .withData(givenSpriteData, sizeof(givenSpriteData))
            .withSize(givenSpriteSize)
            .withAnimated(givenNumberOfFrames, givenAnimationDelay)
            .withLocation(1,1)
            .buildPtr();
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

std::shared_ptr<Sprite> Enemy::getImage() {
    return image;
}

