//
// Created by matthias on 16/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BUCKETHEADZOMBIE_H
#define GBA_SPRITE_ENGINE_PROJECT_BUCKETHEADZOMBIE_H

#include "Enemies/Zombie.h"

class BucketheadZombie: public Zombie {
public:
    BucketheadZombie(int row, std::unique_ptr<Sprite> image);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BUCKETHEADZOMBIE_H
