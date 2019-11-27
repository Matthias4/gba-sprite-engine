//
// Created by michi on 27/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H
#define GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H

#include "Minions/Minion.h"

class Shooter: public Minion {
private:
    int firingRate;
    int damage;
public:
    int getFiringRate();
    int getDamage();
    void shoot() override; //Als we shoot weghalen bij Minion, dan moet hier de override weg.
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H
