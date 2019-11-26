//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MINION_H
#define GBA_SPRITE_ENGINE_PROJECT_MINION_H

#include <libgba-sprite-engine/scene.h>

class Minion {
private:           //Willen we de variabelen private maken en getters gebruiken? Of de variabelen public?
    int health;
    int cost;
    int firingRate;
    int damage;
    int cooldownTime;

    std::unique_ptr<Sprite> image;

public:
    virtual int getHealth() = 0;
    virtual int getCost() = 0;
    virtual int getFiringRate() = 0;
    virtual int getDamage() = 0;
    virtual int getCooldownTime() = 0;

    Minion();
    void shoot();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_MINION_H
