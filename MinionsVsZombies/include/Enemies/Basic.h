//
// Created by matthias on 12/1/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BASIC_H
#define GBA_SPRITE_ENGINE_PROJECT_BASIC_H

#include "Zombie.h"

class Basic: public Zombie {
private:

public:
    Basic(int row, std::unique_ptr<Sprite> image);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BASIC_H
