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
    int getHealth();
    int getCost();
    int getFiringRate();
    int getDamage();
    int getCooldownTime();

    Minion();
    void shoot();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_MINION_H
