//
// Created by matthias on 16/12/2019.
//

#include "Enemies/ConeheadZombie.h"

ConeheadZombie::ConeheadZombie(int row, std::unique_ptr<Sprite> image) : Zombie(15, 4, 2, row, std::move(image)) {}
