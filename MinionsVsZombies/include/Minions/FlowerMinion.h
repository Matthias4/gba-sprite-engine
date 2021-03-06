//
// Created by michi on 26/11/2019.
//

#include <MinionTypes.h>
#include "Minion.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
#define GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H

class FlowerMinion: public Minion {
private:
    int sunPower;
public:
    FlowerMinion(int health, int cost, int cooldownTime, int sunPower, std::unique_ptr<Sprite> image, int creationTime) : Minion(FLOWER_MINION, health, cost, cooldownTime, std::move(image), creationTime) {
        this->sunPower = sunPower;
    };
    //using Minion::Minion;// Constructor inheritance, see https://stackoverflow.com/questions/347358/inheriting-constructors
    int getSunPower();
    void produceSun();
    void shoot() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
