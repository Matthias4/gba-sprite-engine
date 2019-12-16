//
// Created by matthias on 12/1/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BASICZOMBIE_H
#define GBA_SPRITE_ENGINE_PROJECT_BASICZOMBIE_H

#include "Zombie.h"

class BasicZombie: public Zombie {
public:
    BasicZombie(int row, std::unique_ptr<Sprite> image);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BASICZOMBIE_H
