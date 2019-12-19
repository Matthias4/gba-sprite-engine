//
// Created by michi on 27/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H
#define GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H

#include "Minions/Minion.h"
#include "MinionTypes.h"

class Shooter: public Minion {
private:
    int firingRate;
    int damage = 5;
public:
    Shooter(int health, int cost, int cooldownTime, std::unique_ptr<Sprite> image, int creationTime) : Minion(SHOOTER_MINION, health, cost, cooldownTime, std::move(image), creationTime) {};
    //using Minion::Minion;// Constructor inheritance, see https://stackoverflow.com/questions/347358/inheriting-constructors
    int getFiringRate();
    int getDamage();
    void shoot() override; //Als we shoot weghalen bij Minion, dan moet hier de override weg.
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SHOOTER_H
