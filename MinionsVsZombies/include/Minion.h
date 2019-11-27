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
    virtual void shoot() = 0; //FIXME: moeten we deze functie wegdoen? En gewoon bij shooter zetten?
                                // Zoja, waar moeten we dan virtual zetten? Moet we een functie getPlanted() hebben ofzo waar we
                                // virtual bij kunnen zetten?

};


#endif //GBA_SPRITE_ENGINE_PROJECT_MINION_H
