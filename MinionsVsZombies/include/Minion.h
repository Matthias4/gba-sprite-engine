//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MINION_H
#define GBA_SPRITE_ENGINE_PROJECT_MINION_H

#include <libgba-sprite-engine/scene.h>

class Minion {
private:
    int health;
    int cost;
    int cooldownTime;

    std::unique_ptr<Sprite> image;

public:
    int getHealth();
    int getCost();
    int getCooldownTime();

    Minion(int health, int cost, int cooldownTime, std::unique_ptr<Sprite> image);
    virtual void shoot() = 0;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_MINION_H
