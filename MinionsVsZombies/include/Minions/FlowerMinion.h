//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
#define GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H

#include "Minion.h"

class FlowerMinion: Minion {
private:
    int sunPower;
    int productionRate;
public:
    int getSunPower();
    int getProductionRate();
    void produceSun(); //FIXME: moet dit een void zijn? Of willen we dat die iets teruggeeft waar het level iets mee kan doen? Een boolean ofzo?
};


#endif //GBA_SPRITE_ENGINE_PROJECT_FLOWERMINION_H
