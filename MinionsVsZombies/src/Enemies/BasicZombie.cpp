//
// Created by matthias on 12/1/19.
//

#include "Enemies/BasicZombie.h"

BasicZombie::BasicZombie(int givenRow, std::unique_ptr<Sprite> givenImage) : Zombie(10, 5, 2, givenRow, std::move(givenImage)) {}
