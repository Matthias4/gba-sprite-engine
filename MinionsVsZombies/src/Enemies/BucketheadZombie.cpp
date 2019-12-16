//
// Created by matthias on 16/12/2019.
//

#include "Enemies/BucketheadZombie.h"

BucketheadZombie::BucketheadZombie(int row, std::unique_ptr<Sprite> image, int creationTime) : Zombie(20, 2, 2, row, std::move(image), creationTime) {}
