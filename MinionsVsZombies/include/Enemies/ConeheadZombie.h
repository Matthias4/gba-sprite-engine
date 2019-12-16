//
// Created by matthias on 16/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CONEHEADZOMBIE_H
#define GBA_SPRITE_ENGINE_PROJECT_CONEHEADZOMBIE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include "Enemies/Zombie.h"

class ConeheadZombie: public Zombie {
public:
    ConeheadZombie(int row, std::unique_ptr<Sprite> image, int creationTime);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CONEHEADZOMBIE_H
