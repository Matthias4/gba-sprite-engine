//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMY_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Enemy {
private:
    int health;
    std::shared_ptr<Sprite> image;
public:
    int getHealth();
    Enemy(int health, void* spriteData, SpriteSize spriteSize, int numberOfFrames, int animationDelay);
    void getHit(int damage);
    void die();
    std::shared_ptr<Sprite> getImage();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
