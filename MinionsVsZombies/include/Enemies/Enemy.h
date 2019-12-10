//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMY_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Enemy {
private:
    int health;
    std::unique_ptr<Sprite> image;
public:
    Enemy(int health, std::unique_ptr<Sprite> image) : health(health), image(std::move(image)) {};

    int getHealth();
    void getHit(int damage);
    void die();

    void move(int x, int y);
    Sprite *getSprite() { return image.get(); };
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
