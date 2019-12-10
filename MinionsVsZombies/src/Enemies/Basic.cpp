//
// Created by matthias on 12/1/19.
//

#include "Enemies/Basic.h"

Basic::Basic(int givenRow, std::unique_ptr<Sprite> givenImage): Zombie(4, 1, 1, givenRow, std::move(givenImage)){}
