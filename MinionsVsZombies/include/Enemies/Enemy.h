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
    Enemy(int health, std::shared_ptr<Sprite> image);
    void getHit(int damage); //Als een banaan een Enemy raakt, gaat er wat van zijn health af, de int damage is om te weten hoeveel (afhankelijk van wie de shooter was)
    void die();

    Sprite *getSprite();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
