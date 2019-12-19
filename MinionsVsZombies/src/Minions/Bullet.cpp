//
// Created by michi on 12/12/2019.
//

#include "Minions/Bullet.h"

Bullet::Bullet(int originalPositionX, int creationTime, int row, std::unique_ptr<Sprite> image) {
    this->originalPositionX = originalPositionX;
    this->creationTime = creationTime;
    this->row = row;
    this->image = std::move(image);
}

int Bullet::getOriginalPositionX() {
    return originalPositionX;
}

int Bullet::getCreationTime() {
    return creationTime;
}

int Bullet::getRow() {
    return row;
}

Sprite *Bullet::getSprite() {
    return image.get();
}

void Bullet::move(int x, int y) {
    image->moveTo(x, y);
}