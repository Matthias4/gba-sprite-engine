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
    Enemy(int health, std::unique_ptr<Sprite> image);

    int getHealth();
    void getHit(int damage); //Als een banaan een Enemy raakt, gaat er wat van zijn health af, de int damage is om te weten hoeveel (afhankelijk van wie de shooter was)
    void die();

    void move(int x, int y);

    Sprite *getSprite();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
