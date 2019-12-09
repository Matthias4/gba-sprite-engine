//
// Created by michi on 26/11/2019.
//

#include "Minion.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
#define GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H

class FlowerMinion: public Minion {
private:
    int sunPower;
    int productionRate;
public:
    using Minion::Minion;// Constructor inheritance, see https://stackoverflow.com/questions/347358/inheriting-constructors
    int getSunPower();
    int getProductionRate();
    void produceSun(); //FIXME: moet dit een void zijn? Of willen we dat die iets teruggeeft waar het level iets mee kan doen? Een boolean ofzo?
    void shoot() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
